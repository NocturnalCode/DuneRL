/*
 *  Object.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#include "Object.h"
#include "Map.h"
#include "Tile.h"
#include "Ascii.h"

Object::Object()
{
	parent = NULL;
	asciis = new AsciiGroup(new Ascii());

    _flags.passable = NO;
    _flags.transparent = NO;
    _flags.stackable = NO;
    _flags.carryable = NO;
    _flags.holdable = NO;
    _flags.wieldable = NO;
    _flags.wearable = NO;
    _flags.consumable = NO;
    _flags.liquid = NO;
    _flags.terrain = YES;
    _flags.decays = NO;
    
    weight = 0.1;
    range = 1;
    description = "something indescribable";
    iarticle = "a ";
    darticle = "the ";
    decay = 1;
    lastMovementTurn = 0;
}

Object::Object(Ascii *asc) 
{
	parent = NULL;
	asciis = new AsciiGroup(asc);

    _flags.passable = YES;
    _flags.transparent = YES;
    _flags.stackable = NO;
    _flags.carryable = NO;
    _flags.holdable = NO;
    _flags.wieldable = NO;
    _flags.wearable = NO;
    _flags.consumable = NO;
    _flags.liquid = NO;
    _flags.terrain = YES;
    _flags.decays = NO;
    
    weight = 0.1;
    range = 1;
    inventory = NULL;
    description = "something indescribable";
    iarticle = "a ";
    darticle = "the ";
    decay = 1;
    lastMovementTurn = 0;
}

Object::Object(AsciiGroup *asc)
{
	parent = NULL;
	asciis = asc; 
    
    _flags.liquid = NO;
    _flags.passable = YES;
    _flags.transparent = YES;
    _flags.stackable = NO;
    _flags.carryable = NO;
    _flags.holdable = NO;
    _flags.wieldable = NO;
    _flags.wearable = NO;
    _flags.consumable = NO;
    _flags.liquid = NO;
    _flags.terrain = NO;
    _flags.decays = NO;
    
    weight = 0.1;
    range = 1;
    inventory = NULL;
    description = "something indescribable";
    iarticle = "a ";
    darticle = "the ";
    decay = 1;
    lastMovementTurn = 0;
}

Object::~Object()
{
    //printf("deallocating object");
    parent = NULL;
    delete asciis;
    asciis = NULL;
    if (inventory != NULL) {
        delete inventory;
    }
}

void Object::removeFromTile()
{
    if(parent)
    {
        didLeaveTile(parent);
        parent->removeObject(this);
        
    }
}

void Object::setParent(Tile *tile)
{
    didEnterTile(tile);
	parent = tile;
}

Tile* Object::getParent()
{
	return parent;
}

Point Object::getPosition()
{
    if(parent == NULL)
        return Point();
	return parent->Position;
}

Map *Object::getMap()
{
    if(parent == NULL)
        return NULL;
    return parent->parent;
}

void Object::setPassable(bool passable)
{
	if(passable)
		_flags.passable = YES;
	else
		_flags.passable = NO;
}

bool Object::passable()
{
	return _flags.passable==YES;
}

void Object::setTransparent(bool transparent)
{
	if(transparent)
		_flags.transparent = YES;
	else
		_flags.transparent = NO;
}

bool Object::transparent()
{
	return _flags.transparent==YES;
}

void Object::setTerrain(bool terrain)
{
	if(terrain)
		_flags.terrain = YES;
	else
		_flags.terrain = NO;
}

bool Object::terrain()
{
	return _flags.terrain==YES;
}

void Object::setLiquid(bool liquid)
{
	if(liquid)
		_flags.liquid = YES;
	else
		_flags.liquid = NO;
}

bool Object::liquid()
{
	return _flags.liquid==YES;
}

bool Object::canBeCarried()
{
    return (_flags.carryable|_flags.wearable|_flags.holdable|_flags.wieldable)==YES;
}

Ascii* Object::getAscii()
{
    if(asciis == NULL)
        asciis = new AsciiGroup(new Ascii());//return NULL; //new Ascii(); //cant just be allocating things and not concerned about releasing them
	return asciis->currentAscii();
}

void Object::updateAscii()
{
	asciis->update();
}

void Object::addObjectToInventory(Object *object)
{
    if(inventory == NULL)
        inventory = new std::list<Object *>();
    inventory->push_back(object);
}

void Object::removeObjectFromInventory(Object *object)
{
    if(inventory == NULL)
        return;
    inventory->remove(object);
}

Objects *Object::getInventory()
{
    return inventory;
}

void Object::dumpInventory()
{
    if(inventory == NULL)
        return;
    foreachp(std::list<Object *>, object, inventory)
    {
        dropInventoryObject((*object));
    }
}

void Object::dropInventoryObject(Object *object)
{
    // todo
}

Damages Object::getMeleeDamages()
{
    Damages dmgs;
    dmgs.push_back(Damage(weight*20,DamageBlunt));
    return dmgs;
}

Damages Object::calculateMeleeDamagesFrom(Object *object)
{
    Damages raw = object->getMeleeDamages();
    // reduce damage from armour, resistances, whatever 
    
    return raw;
}

Damages Object::getThrowDamages()
{
    Damages dmgs;
    dmgs.push_back(Damage(weight*10,DamageBlunt));
    return dmgs;
}

void Object::onDeath()
{
    
}

void Object::onDamagedBy(Object *attacker,Damage damage)
{
    
}

void Object::onHealedBy(Object *attacker,Damage damage)
{
    
}

void Object::onDamagedObject(Object *target,Damage damage)
{
    
}

void Object::didEnterTile(Tile *tile)
{
    
}
void Object::didLeaveTile(Tile *tile)
{
    
}

float Object::distanceTo(Object *object)
{
    return getPosition().distance(object->getPosition());
}

void Object::update(Speed turnSpeed, int turnNumber)
{
    
}
