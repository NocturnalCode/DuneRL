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
    
    bool spiceCrazed; // would like to abstract to some generic effect
    
    int spice;
    int water,minWater,maxWater;

public:
    // UI related fields
    std::string family;
    std::string spiceDescription();
    std::string waterDescription();
    
    std::string underfootDescription();
    
    Player();
};

#endif /* PLAYER_H_INC */