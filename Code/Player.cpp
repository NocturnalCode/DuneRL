/*
 *  Player.cpp
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#include "Player.h"
#include "Stringer.h"

Player::Player() : Monster(new Ascii(64,1.0,0,0))
{
	behaviour = BehaviourNone;
    sight = 40;
    name = "Leto";
    family = "Atreides";
    maxWater = 10;
    water = maxWater;
    spice = 0;
    spiceCrazed = false;
    kills = 0;
}

std::string Player::spiceDescription()
{
    return stringFormat("%d Spice",spice);
}
std::string Player::waterDescription()
{
    std::string description;
    if(spiceCrazed)
        description = "#0ffSpice Madness";
    else
    {    
        if(water <= 0)
            description = "#f00Dying"; // you'll be losing health now
        else if(water <= maxWater/2)
            description = "#f82Dehydrated";
        else if(water <= 3*maxWater/4)
            description = "#ff0Thirsty";
        else
            description = "#0f0Hydrated";
    }
    
    return description + stringFormat("< %d/%d>",water,maxWater);
}

std::string Player::underfootDescription()
{
    return "It is sandy underfoot.";// it's dune it's always sand
}