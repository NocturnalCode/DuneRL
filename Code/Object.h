/*
 *  Object.h
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#ifndef OBJECT_H_INC
#define OBJECT_H_INC 

#include "Types.h"
#include <vector>
#include <list>

#include "Ascii.h"
#include "Damage.h"

#include "Point.h"
#include "Effect.h"

class Map;
class Tile;

typedef enum {
	SpeedFrozen,
	SpeedSlow,
	SpeedNormal,
	SpeedFast,
    // Keep SpeedCount at bottom
    SpeedCount
} Speed;

typedef struct 
{
	unsigned passable:1;
	unsigned transparent:1;
    unsigned stackable:1;
    unsigned carryable:1;
    unsigned holdable:1;
    unsigned wieldable:1;
    unsigned wearable:1;
    unsigned consumable:1;
    unsigned liquid:1;
    unsigned terrain:1;
    unsigned decays:1;
	unsigned _reserved:22;
} ObjectFlags;

class Object {
protected:
    AsciiGroup *asciis;
    Objects *inventory;
    Effects effects;
    int lastMovementTurn;
public:
    Tile *parent;
    std::string name;
    std::string description;
    std::string iarticle,darticle;
    std::string stackName;
    float weight;
    int range;
    int decay;
    int count;
    
    int oid;
    
    ObjectFlags _flags;
    
    Object();
    Object(Ascii *ascii);
    Object(AsciiGroup *ascii);
    virtual ~Object();
    void setParent(Tile *tile);
    Tile* getParent();
    
    Map *getMap();
    void removeFromTile();
    virtual void onDeath();
    virtual void onDamagedBy(Object *attacker,Damage damage);
    virtual void onHealedBy(Object *attacker,Damage damage);
    virtual void onDamagedObject(Object *target,Damage damage);
    
    float distanceTo(Object *object);
    
    Point getPosition();
    
    void setPassable(bool passable);
    bool passable();
    
    void setTransparent(bool transparent);
    bool transparent();
    
    void setTerrain(bool terrain);
    bool terrain();
    
    void setLiquid(bool liquid);
    bool liquid();
    
    void addEffect(Effect *effect);
    void removeEffect(Effect *effect);
    
    bool canBeCarried();
    
    virtual Damages getMeleeDamages();
    virtual Damages getThrowDamages();
    virtual Damages getRangedDamages();
    
    virtual Damages calculateMeleeDamagesFrom(Object *object);
    virtual Damages calculateRangedDamagesFrom(Object *object);
    
    Ascii* getAscii();
    virtual void updateAscii();
    
    virtual void addObjectToInventory(Object *object);
    virtual void removeObjectFromInventory(Object *object); 
    virtual Objects *getInventory();
    virtual void dumpInventory();
    virtual void dropInventoryObject(Object *object);
    
    virtual void didEnterTile(Tile *tile);
    virtual void didLeaveTile(Tile *tile);
    
    void update(Speed turnSpeed, int turnNumber);
    virtual void doUpdate(Speed turnSpeed);
    
    void setDecays(int numberOfTurns);
};

#endif /* OBJECT_H_INC  */

/*
 
 ADOMs itemset:
 
 [  Armor, shields, cloaks, boots, girdles, gauntlets and helmets
 *  Gems and rocks
 ]  Tools (keys, writing sets, elemental orbs, and various other things)
 '  Necklaces
 (  Melee weapons (all of them)
 }  Missile weapons (bows, crossbows, slings)
 /  Missiles (arrows, quarrels, etc)
 =  Rings
 \  Wands
 !  Potions
 ?  Scrolls
 ~  Bracers
 %  Food (inc corpses and herbs)
 $  Gold
 {  Musical Instruments
 "  Books
 
 
 Angband items:
 
 , : Food, Mushrooms
 | : Edged weapon
 \ : Hafted weapon, Shovel, Pick
 / : Polearm
 } : Sling, Bow, Crossbow
 { : Ammo
 ] : Armor
 ( : Armor
 [ : Armor
 ) : Shield
 = : Ring
 " : Amulet
 ? : Scrolls, Books
 ! : Potions
 - : Wands, Rods
 _ : Staffs
 ~ : Junk, Chest, Torch, Bones, Some magic light sources
 $ : Treasure
 & : Pile of mixed items.
 
 */

