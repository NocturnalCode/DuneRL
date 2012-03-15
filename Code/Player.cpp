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

#include "Melee.h"
#include "Ranged.h"
#include "Shield.h"

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
    
    darticle = "";
    iarticle = "";
	behaviour = BehaviourNone;
    sight = 45;
    setMaxHP(10);
    maxWater = (TURNS_IN_A_DAY * 1.5f/15.0f)/3;
    water = maxWater;
    waterTick = 0;
    rateOfDehydration = TURNS_IN_A_DAY_PART;
    spice = 0;
    spiceCrazed = false;
    kills = 0;
    description = "You";
    
    inventory = new Objects();
    equipment = new ObjectMap();
    
    Melee *melee = new Melee();
    addObjectToInventory(melee);
    equip(melee);
}

Player::~Player()
{
    printf("Destructing Player");
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

void Player::equip(Object *object)
{
    if(equipment == NULL)
        equipment = new ObjectMap();
    
    Melee *melee = dynamic_cast<Melee *>(object);
    if(melee != NULL)
    {
        // check previous 
        // was unequipped
        
        (*equipment)["Melee"] = object;
        
        // was equipped
        return;
    }
    Ranged *ranged = dynamic_cast<Ranged *>(object);
    if(ranged != NULL)
    {
        // check previous 
        // was unequipped
        
        (*equipment)["Ranged"] = object;
        
        // was equipped
        return;
    }
    Shield *shield = dynamic_cast<Shield *>(object);
    if(shield != NULL)
    {
        // check previous 
        // was unequipped
        
        (*equipment)["Shield"] = object;
        
        // was equipped
        return;
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
        LOG("You feel thirstier.");
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
        sightMap->addFilter(new LightFilterShadow());
        sightMap->addFilter(new LightFilterDayNightCycle());
    }
}