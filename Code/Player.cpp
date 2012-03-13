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
#include "LightFilterDayNightCycle.h"
#include "LightFilterShadow.h"

#include "DuneWorld.h"

Player::Player() : Monster(new Ascii(64,Colour::red(), Colour::clear()))//Monster(new Ascii(64,1.0,0,0))
{
    if(arc4random()%2==0)
    {
        name = "Feyd Rautha";
        family = "Harkonnen";
    }
    else
    {
        name = "Leto Atreides";
        family = "Atreides";
    }
    
	behaviour = BehaviourNone;
    sight = 40;

    setMaxHP(10);
    maxWater = TURNS_IN_A_DAY * 1.5f;
    water = maxWater;
    waterTick = 0;
    rateOfDehydration = TURNS_IN_A_DAY_PART;
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
    if(isAlive() || DEV)
        return parent->description();
    return "You will stand amongt the dunes no more.";
}

void Player::onDeath()
{
    if(DEV)
        LOG("%s would have died, but is apparently too good for that.",this->name.c_str());
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
        LOG("You feel thirster.");
        waterTick = 0;
        water--;
    }
    
    if(water < 0 && !spiceCrazed)
    {
        if(!DEV)
        {
            LOG("Losing health from dehydration.");
            adjustHP(-1);
        }
    }
}

void Player::calculateSight()
{
    if(isAlive())
    {
        sightMap = new Lightmap(getPosition(),sight,getMap());
        //sightMap->addFilter(new LightFilterShadow());
    }
}