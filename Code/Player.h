/*
 *  Player.h
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#ifndef PLAYER_H_INC
#define PLAYER_H_INC 

#include "Monster.h"
class SpiceMadness;

typedef struct {
//	unsigned passable:1;
//	unsigned transparent:1;
	unsigned _reserved:32;
} PlayerFlags;

class Player: public Monster
{
protected:
    PlayerFlags _flags;
    int kills;
    
    SpiceMadness *spiceMadnessEffect();

    int water,minWater,maxWater;
    int rateOfDehydration;
    int waterTick;
    
    void performTurn();
    void onDeath();
    
    void didEquipObject(Object *object);
    void didUnequipObject(Object *object);
    void didDropObject(Object *object);
    void didPickupObject(Object *object);
    void didConsumeObject(Object *object);
    
    void hydrate(int amount);
    
    virtual void didEnterTile(Tile *tile);

public:
    // UI related fields
    std::string family;
    std::string spiceDescription();
    std::string waterDescription();
    
    std::string underfootDescription();
    void calculateSight();
    
    bool equip(Object *object);
    int spiceCount();
    bool isAlive();
    Player();
    ~Player();
};

#endif /* PLAYER_H_INC */