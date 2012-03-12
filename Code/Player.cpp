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
#include "DuneRL.h"
#include "Tile.h"

Player::Player() : Monster(new Ascii(64,Colour::red(), Colour::clear()))//Monster(new Ascii(64,1.0,0,0))
{
	behaviour = BehaviourNone;
    sight = 40;
    name = "Leto";
    family = "Atreides";
    maxWater = 20;
    water = maxWater;
    waterTick = 0;
    rateOfDehydration = 15;
    spice = 0;
    spiceCrazed = false;
    kills = 0;
    description = "You";
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
    if(isAlive())
        return parent->description();
    return "You are stand amongt the dunes no more.";
}

void Player::onDeath()
{
    if(DEV)
        LOG("#AA0%s would have died, but is apparently too good for that.",this->name.c_str());
    else
    {
        Monster::onDeath();
        DuneRL::shared->deathMenu();
    }
}

// a turn has past
void Player::performTurn()
{
    //decrement water;
    if(!spiceCrazed)
        waterTick++;
    
    if(waterTick >= rateOfDehydration)
    {
        LOG("You feel thirster");
        waterTick = 0;
        water--;
    }
    
    if(water < 0 && !spiceCrazed)
    {
        LOG("Losing health from dehydration");
        adjustHP(-1);
    }
}