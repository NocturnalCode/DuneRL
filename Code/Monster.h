/*
 *  Monster.h
 *  Roguelike
 *
 *  Created by Daniel on 13/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef MONSTER_H_INC
#define MONSTER_H_INC 

#include "Object.h"
#include "Types.h"
#include "Lightmap.h"
//#include "Stringer.h"

class Weapon;
class RangeFilter;


#define BehaviourNone       1<<0
#define BehaviourPassive    1<<1
#define BehaviourAggressive 1<<2
#define BehaviourDefensive  1<<3
#define BehaviourFlees      1<<4
#define BehaviourTimid      1<<5
#define BehaviourCount      6

typedef int BehaviourMask;

typedef struct {
//	unsigned passable:1;
//	unsigned transparent:1;
	unsigned _reserved:32;
} MonsterFlags;

typedef struct {
	// covert

	// combat
	
	// faith
	
	// magic 
	
	// crafting
	
	// general
} Skills;

class Monster: public Object
{
protected:
    MonsterFlags _flags;
    Lightmap *sightMap;
    
    unsigned hp,maxhp;
    unsigned mp,maxmp;

    ObjectMap *equipment;

    WorldCoord randomMove();
    WorldCoord towardAttacker(Object *attacker);
    WorldCoord awayFromAttacker(Object *attacker);

    Objects attackers;
    //RangeFilter *rangeFilter;
public:

    unsigned sight;
    Speed speed;
    BehaviourMask behaviour;

    Monster();
    Monster(Ascii *ascii);

    virtual ~Monster();
    int getHP();
    int adjustHP(int delta);
    void setHP(int hitpoints);
    std::string hpDescription();
    
    int getMaxHP();
    void setMaxHP(int maxHitPoints);

    Objects getWeaponsForMelee();
    Object *getWeaponForRanged(); 

    virtual Damages getMeleeDamages();
    
    virtual void dropInventoryObject(Object *object);
    virtual void dumpInventory();
    virtual bool equip(Object *object);
    virtual bool unequip(Object *object);
    virtual bool consume(Object *object);
    virtual bool objectIsEquipped(Object *object);
    
    virtual void updateAscii();
    virtual void performTurn();

    virtual void calculateSight();
    virtual bool canSee(int x, int y);
    
    static void load();
    
    void attack(Object *target, Object *weapon=NULL);
    void fire(Object *target, Object *weapon);
    
    virtual bool isAlive();
    
    virtual void onDeath();
    virtual void onDamagedBy(Object *attacker,Damage damage);
    
    virtual void didEnterTile(Tile *tile);
    virtual void didLeaveTile(Tile *tile);
    
    virtual void didConsumeObject(Object *object);
    
    virtual void didEquipObject(Object *object);
    virtual void didUnequipObject(Object *object);
    
    virtual void didDropObject(Object *object);
    virtual void didPickupObject(Object *object);
    
    Lightmap* getSightMap();
    virtual void doUpdate(Speed turnSpeed);
    
    virtual void makeRangeOverlay(int rangeValue);
//  virtual void onHealedBy(Object *attacker,Damage damage);
};

inline std::string stringForSpeed(Speed s)
{
	std::string name;
	switch((int)s)
	{
		case SpeedSlow:
			name = "Slow";
			break;
		case SpeedNormal:
			name = "Normal";
			break;
		case SpeedFast:
			name = "Fast";
			break;
        default:
            name = "Frozen";
            break;
	}
	return name;
}

inline std::string stringForBehaviour(BehaviourMask behaviour)
{
	std::string name = "";
    
    for(int i=0; i< BehaviourCount; i++)
    {
        if(NOT_MASK(behaviour,1<<i))
            continue;
        
        int flag = 1<<i;
        switch(flag)
        {
            case BehaviourNone:
                name += "None ";
                break;
            case BehaviourPassive:
                name += "Passive ";
                break;
            case BehaviourAggressive:
                name += "Aggressive ";
                break;
            case BehaviourDefensive:
                name += "Defensive ";
                break;
            case BehaviourFlees:
                name += "Flees ";
                break;
            case BehaviourTimid:
                name += "Timid ";
                break;
            default:
                name += "Undefined ";
                break;
        }
    }
    //printf("behaviour value: %d\n", behaviour);
	return name;
}

#endif /* MONSTER_H_INC */
