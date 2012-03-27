/*
 *  Monster.cpp
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Monster.h"
#include "Types.h"
#include "Tile.h"
#include "Map.h"
#include "Player.h"
#include "Ascii.h"
#include "Roguelike.h"

#include "Corpse.h"
#include "Blood.h"
#include "Stringer.h"
#include "RangeFilter.h"

Monster::Monster() : Object()
{
	hp = maxhp = 1;
	mp = maxmp = 0;
	sight = 10;
	speed = SpeedNormal; 
    name = "Monster";
    
    setTransparent(true);
	setPassable(false);
    //rangeFilter = NULL;
    equipment = NULL;
    
    behaviour = BehaviourDefensive;
	sightMap = NULL;
}

Monster::Monster(Ascii *ascii) : Object(ascii)
{
	hp = maxhp = 1;
	mp = maxmp = 0;
	sight = 10;
	speed = SpeedNormal;
    name = "Monster";
    
    setTransparent(true);
	setPassable(false);
    
    equipment = NULL;
    
    behaviour = BehaviourDefensive;
   // rangeFilter = NULL;
	sightMap = NULL;
}

Monster::~Monster()
{
//    if (rangeFilter) {
//        delete rangeFilter;
//    }
}

int Monster::getHP()
{
    return hp;
}

int Monster::adjustHP(int delta)
{
    setHP(hp + delta);
    return hp;
}

void Monster::setHP(int hitpoints)
{
    if(hitpoints > maxhp)
        hp = maxhp;
    else if(hitpoints <= 0)
    {
        hp = 0;
        onDeath();
    }
    else
    {
        hp = hitpoints;
    }
}

std::string Monster::hpDescription()
{
    std::string description;
    if(hp <= 0)
        description = "#f00Dead";
    else if(hp <= maxhp/2)
        description = "#f82Wounded";
    else if(hp <= 3*maxhp/4)
        description = "#ff0Injured";
    else
        description = "#0f0Uninjured";
    
    return description + stringFormat("< %d/%d>",hp,maxhp);
}

int Monster::getMaxHP()
{
    return maxhp;
}

void Monster::setMaxHP(int maxHitPoints)
{
    maxhp = maxHitPoints;
    if(maxhp <= 0)
        maxhp = 1;
    hp = maxhp;
}

void Monster::updateAscii()
{
	Object::updateAscii();
}

WorldCoord Monster::randomMove()
{
    int x=0,y=0;
    switch(rand()%4)
    {
        case 0: //left
            x=-1;
            break;
        case 1: //right
            x=1;
            break;
        case 2: //up
            y=-1;
            break;
        case 3: //down
            y=1;
            break;
            
    }
    
    WorldCoord current = this->getPosition();
    WorldCoord random(current.X+x,current.Y+y);
    
    return random;
}

WorldCoord Monster::towardAttacker(Object *target)
{
    // two main movements are possible in four connected, effectively one square in the x or y toward the target, eg left or up, up or right, down or left, down or right
    WorldCoord move;
    WorldCoord p = getPosition();
    WorldCoord t = target->getPosition();
    
    int xdir = p.X > t.X ? -1 : p.X == t.X ? 0 : 1;
    int ydir = p.Y > t.Y ? -1 : p.Y == t.Y ? 0 :1;
    
    if (abs(p.X - t.X) < abs(p.Y - t.Y)) {
        xdir = 0;
    }
    
    // check move in X dir
    if (xdir != 0) {
        move = WorldCoord(p.X+xdir,p.Y);
        if(getMap()->checkMove(this, move.X, move.Y))
        {
            return move;
        }
    }
    // check move in Y dir
    move = WorldCoord(p.X,p.Y+ydir);
    if(getMap()->checkMove(this, move.X, move.Y))
    {
        return move;
    }
       
    return  WorldCoord(0,0);
}

WorldCoord Monster::awayFromAttacker(Object *target)
{
    if(target==NULL)
        return WorldCoord(0,0);
    /// same as above just opposite direction
    
    Map *map = target->getMap();
    
    WorldCoord move;
    WorldCoord p = getPosition();
    WorldCoord t = target->getPosition();
    
    int xdir = p.X > t.X ? 1 : p.X == t.X ? 0 : -1;
    int ydir = p.Y > t.Y ? 1 : p.Y == t.Y ? 0 : -1;
    
    if (abs(p.X - t.X) < abs(p.Y - t.Y)) {
        xdir = 0;
    }
    
    // check move in X dir
    if (xdir != 0) {
        move = WorldCoord(p.X+xdir,p.Y);
        if(map->checkMove(this, move.X, move.Y))
        {
            return move;
        }
    }
    
    // check move in Y dir
    move = WorldCoord(p.X,p.Y+ydir);
    if(map->checkMove(this, move.X, move.Y))
    {
        return move;
    }
    
    return  WorldCoord(0,0);
}

void Monster::attack(Object *t, Object *weapon)
{
    Monster *target = dynamic_cast<Monster *>(t);
    if(target != NULL)
    {
        Damages damages = target->calculateMeleeDamagesFrom(this);
        foreach(Damages, dmg, damages)
        {
            Damage damage = (*dmg);
            LOG("Hit %s.< #AA0%d dmg>",target->name.c_str(),damage.damage);
            target->adjustHP(-damage.damage);
            printf("<%s.>",target->hpDescription().c_str());
            
            target->onDamagedBy(this, damage);
            this->onDamagedObject(target,damage);
        }
    }
}

void Monster::fire(Object *t, Object *weapon)
{
    Monster *target = dynamic_cast<Monster *>(t);
    if(target != NULL)
    {
        Damages damages = target->calculateRangedDamagesFrom(this);
        foreach(Damages, dmg, damages)
        {
            Damage damage = (*dmg);
            LOG("Hit %s.< #AA0%d dmg>",target->name.c_str(),damage.damage);
            target->adjustHP(-damage.damage);
            printf("<%s.>",target->hpDescription().c_str());
            
            target->onDamagedBy(this, damage);
            this->onDamagedObject(target,damage);
        }
    }
}

//void Monster::throwObject(Object *t, Object *weapon)
//{
//    Monster *target = dynamic_cast<Monster *>(t);
//    if(target != NULL)
//    {
//        Damages damages = target->calculateMeleeDamagesFrom(this);
//        foreach(Damages, dmg, damages)
//        {
//            Damage damage = (*dmg);
//            LOG("Hit %s.< #AA0%d dmg>",target->name.c_str(),damage.damage);
//            target->adjustHP(-damage.damage);
//            printf("<%s.>",target->hpDescription().c_str());
//            
//            target->onDamagedBy(this, damage);
//            this->onDamagedObject(target,damage);
//        }
//    }
//}

void Monster::performTurn()
{
    if(hp <= 0 || behaviour==BehaviourNone)
        return;
     
    WorldCoord move;
    Map *map = getMap();
    
    if(HAS_MASK(behaviour,BehaviourAggressive)||HAS_MASK(behaviour,BehaviourTimid))
    {
        // check for people to attack
        attackers = map->getVisibleMonsters(this,sight);
    }
    
    Object *nearest = NULL;
    float mindist = sight+1;
    foreach(Objects, o, attackers)
    {
        float dist = (*o)->distanceTo(this);
        if(dist < mindist && ((*o)->oid != oid))
        {
            nearest = (*o);
            mindist = dist;
        }
    }
    
    if(!attackers.empty())
        //printf("<[%s] %lu attackers (nearest %s)>",this->name.c_str(),attackers.size(),nearest?nearest->name.c_str():" - ");

    /// check flee
    if(HAS_MASK(behaviour,BehaviourFlees))
    {
        if(HAS_MASK(behaviour,BehaviourAggressive) && hp > (maxhp*0.2))
        {
            //printf("<[%s] too aggressive to flee>",this->name.c_str());
        }
        else
        {
            if(!attackers.empty())
            {
                move = awayFromAttacker(nearest);
                //printf("<[%s] fled>",this->name.c_str());
            }
        }
    }
    
    if(!move.zero() && map->checkMove(this, move.X, move.Y))
    {
        map->moveObject(this,move.X,move.Y);
        return;
    }
    
    /// check actions, steal, eat, etc
    /// todo
    
    /// check can attack
    if( nearest && NOT_MASK(behaviour,BehaviourPassive))
    {
        //printf("<[%s] wants to attack %s >",this->name.c_str(),nearest->name.c_str());
        
        Object *ranged = getWeaponForRanged();
        if((ranged!=NULL) && (ranged->range >= mindist))
        {
            fire(nearest,ranged);
            return;
        }
        else if(mindist <= 1)
        {
            attack(nearest);
            return;
        }
    }
    
    /// check movement
    if(nearest && HAS_MASK(behaviour,BehaviourAggressive))
    {
        move = towardAttacker(nearest);
        //printf("<[%s] Wants to move toward target>",this->name.c_str());
    }
    else if(nearest && HAS_MASK(behaviour,BehaviourTimid))
    {
        move = awayFromAttacker(nearest);
        //printf("<[%s] Wants to move away from target>",this->name.c_str());
    }
    
    if(move.zero())
    {
       move = randomMove();
       //printf("<[%s] Wants to move randomly>",this->name.c_str());
    }
    
    if(!move.zero() && map->checkMove(this, move.X, move.Y))
    {
        //LOG("<[%s] moved>",this->name.c_str());
        map->moveObject(this,move.X,move.Y);
    }
    else
    {
        //LOG("<[%s] didn't move>",this->name.c_str());
    }
}

bool Monster::canSee(int x, int y)
{		
	if(sightMap==NULL)
		calculateSight();
	WorldCoord world(x,y);
	bool visible = sightMap->isLit(world);
	return visible;
}

void Monster::didEnterTile(Tile *tile)
{
    if(tile==NULL)
        return;
    
    if(inventory != NULL)
    {
        Objects tmp = *(tile->getObjects());
        foreach(Objects, o, tmp)
        {
            Object *object = (*o);
            if(object->canBeCarried())
            {
                addObjectToInventory(object);
                printf("picked up %s\n",object->name.c_str());
                didPickupObject(object);
            }
        }
    }
}

void Monster::didLeaveTile(Tile *tile)
{
    if(tile==NULL)
        return;
    
    // maybe drop footprints here
    if(arc4random()%4==0)
    {
        Object *footprint = new Object(new Ascii(EXCLAMATION_DOUBLE,Colour::yellow(),Colour::clear()));
        footprint->name = stringFormat("footprints");
        footprint->description = "some footprints";
        footprint->setLiquid(true);
        footprint->setDecays(40);
        parent->addLiquid(footprint);
    }
}

void Monster::dropInventoryObject(Object *object)
{
    if (object == NULL)
        return;
    unequip(object);
    Object::dropInventoryObject(object);
    didDropObject(object);
}

void Monster::calculateSight()
{
    if(isAlive())
    {
        if (sightMap == NULL) {
             sightMap = new Lightmap(getPosition(),sight,getMap());
        }
       
    }
}

/// this is kinda ok for NPCs but isn't very good for player characters
Object *Monster::getWeaponForRanged()
{
    if(equipment == NULL)
        return NULL;
    foreachp(ObjectMap, obj, equipment)
    {
        Object *weapon = obj->second;
        if(weapon->_flags.wieldable && (weapon->range > 1))
        {
            return weapon;
        }
    }
    
    return NULL;
}

void Monster::didEquipObject(Object *object)
{
    // add equip effect
}

void Monster::didUnequipObject(Object *object)
{
    // remove equip effect
}

void Monster::didDropObject(Object *object)
{
    // remove carry effect
}

void Monster::didPickupObject(Object *object)
{
    // add carry effect
}

bool Monster::equip(Object *object)
{
    if(equipment == NULL)
        equipment = new ObjectMap();
    
    if(object->parent != NULL)
        addObjectToInventory(object);
    
    if((object->_flags.wearable|object->_flags.holdable|object->_flags.wieldable)==YES)
    {
        (*equipment)[stringFormat("%d",equipment->size())] = object;
        didEquipObject(object);
        return true;
    }
    return false;
}

bool Monster::unequip(Object *object)
{
    foreachp(ObjectMap, obj, equipment)
    {
        Object *equipped = obj->second;
        if(equipped == object)
        {
            (*equipment)[obj->first] = NULL;
            didUnequipObject(object);
            return true;
        }
    }
    return false;
}

void Monster::didConsumeObject(Object *object)
{
    // add consume effects
}

bool Monster::consume(Object *object)
{
    if(object->_flags.consumable)
    {
        if(object->_flags.stackable == YES)
        {
            object->count--;
            if(object->count > 0)
            {
                didConsumeObject(object);
                return true;
            }
        }
        
        object->removeFromTile();
        unequip(object);
        removeObjectFromInventory(object);
        didConsumeObject(object);
        return true;
    }
    return false;
}

bool Monster::objectIsEquipped(Object *object)
{
    if(equipment == NULL)
        return false;
    foreachp(ObjectMap, obj, equipment)
    {
        Object *equipped = obj->second;
        if(equipped == object)
            return true;
    }
    return false;
}

/// this is more valid than the above ranged version, but still pretty meh
Objects Monster::getWeaponsForMelee()
{    
    Objects weapons;
    
    if(equipment==NULL)
        return weapons;
    
    foreachp(ObjectMap, obj, equipment)
    {
        Object *weapon = obj->second;
        if(weapon== NULL)
            continue;
        
        if(weapon->_flags.wieldable)
        {
            weapons.push_back(weapon);
        }
    }
    
    return weapons;
}

bool Monster::isAlive()
{
    return hp > 0;
}

void Monster::onDeath()
{
    LOG("%s%s died.",this->darticle.c_str(), this->name.c_str());
    // make corpse
    Corpse *corpse =  Armoury::shared->spawn<Corpse>();//  new Corpse(this);
    corpse->name = stringFormat("%s's corpse",this->name.c_str());
    corpse->description = this->darticle  + "corpse of " + this->iarticle + this->name;
    parent->addObject(corpse);
    
    // more gore, body parts perhaps
    
    dumpInventory();
    // remove self
    parent->removeObject(this);
}

Damages Monster::getMeleeDamages()
{
    Damages dmgs;
    Objects weapons = getWeaponsForMelee();
//    foreach(Objects,w,weapons)
//    {
//        dmgs.merge((*w)->getMeleeDamages());
//    }
    
    if(dmgs.empty())
        dmgs.push_back(Damage(1));
    
    return dmgs;
}

void Monster::onDamagedBy(Object *attacker,Damage damage)
{
    attackers.push_back(attacker);
    attackers.unique();
    
    Point splat = awayFromAttacker(attacker);
    
    Map *map = attacker->getMap();
    
    if(!map->checkMove(this, splat.X, splat.Y))
        return;
    
    Colour bloodColour = Colour::red(); // this->bloodColour(); would be nice
    
    //int ascii = arc4random()%2==0?EXCLAMATION:EXCLAMATION_DOUBLE;
    Blood *blood = Armoury::shared->spawn<Blood>();//new Blood(bloodColour);
    blood->name = stringFormat("%s's blood",this->name.c_str());
    blood->description = this->darticle + "the blood of " + this->iarticle + this->name;
    blood->count = 1+(arc4random()+5);
    
    Tile *tile = map->getTile(splat);
    if(tile)
    {
        tile->addLiquid(blood);
        Ascii *topAscii = tile->getTopAscii(true);
        topAscii->Foreground.lerp(bloodColour,0.2);
        
        Ascii *terrainAscii = map->getTile(splat)->getTerainAscii(true);
        terrainAscii->Foreground.lerp(bloodColour,0.2);
    }
    else
    {
        delete blood;
    }
}

void Monster::dumpInventory()
{
    Object::dumpInventory();
    if(equipment == NULL)
        return;
    
    ObjectMap equipment_objs = (*equipment);
    foreach(ObjectMap, object, equipment_objs)
    {
        dropInventoryObject((object->second));
    }
}

Lightmap* Monster::getSightMap()
{
    return sightMap;
}

void Monster::doUpdate(Speed turnSpeed)
{
    Object::doUpdate(turnSpeed);

    if (turnSpeed == speed) {
        if(this->getHP() <= 0)
        {
            //Monster *dead = (*m);
            //m++;
         
            if(this->getMap()->getPlayer() != this)
            {
                this->getMap()->monsters.remove(this);
                //monsters.remove(dead);
                //printf("removing dead monster: %s",dead->name.c_str());
                //delete dead;
            }
            else 
            {
                if(!DEV)
                {
                    LOG("CONGRATULATIONS YOU DIED");
                    //break;
                }
                else
                {
                    if(this->speed == turnSpeed)
                        this->performTurn();
                }
                    
            }
        }
		else if(this->speed == turnSpeed)
			performTurn();
    }
}

void Monster::makeRangeOverlay(int rangeValue)
{
//    Object *wepon = this->getWeaponForRanged();
//    if (wepon != NULL) {
//        int rang = wepon->range;
        
        //if (rangeFilter == NULL) {
    
    Objects visibleMonsters = this->getMap()->getVisibleMonsters(this, rangeValue);
    
    Object *visibleObject = NULL;
    if (visibleMonsters.size()>0) {
        visibleObject = (*(visibleMonsters.begin()));
    }
    
    RangeFilter *rangeFilter = new RangeFilter(Point(1,1));
    //}
    //
    rangeFilter->setMaxRange(rangeValue);
    if (visibleObject) {
        
        LocalCoord dest = this->sightMap->world2localWithoutRadius(visibleObject->getPosition());
        rangeFilter->setDestinationPoint(dest);
    }
    else {
        rangeFilter->setDestinationPoint(Point(1,1));
    }
    
    sightMap->addFilter(rangeFilter);
    
    Roguelike *rogue = Roguelike::shared;
    Window* window = rogue->getRootWindow();
    if (window) {
        window->eventDelegate = rangeFilter;
    }
    
//    }
}
