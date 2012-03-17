//
//  SpiceMadness.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "SpiceMadness.h"
#include "DuneRL.h"

#define MADNESS 150

SpiceMadness::SpiceMadness(int duration, Object *object) : Effect(duration,object)
{
    completeMadness = false;
    madnessFilter = NULL;
}

SpiceMadness::~SpiceMadness()
{
    if (madnessFilter != NULL) {
        delete madnessFilter;
    }
}

bool SpiceMadness::isMad()
{
    return duration > MADNESS;
}

void SpiceMadness::addDuration(int d)
{
    Effect::addDuration(d);
    printf("add spice duration %d\n",d);
    
    if(isMad()) 
    {
        completeMadness = true;
        LOG("Your vision begins to warp and twist.");
        /// add madness filter
        
        Player *player = dynamic_cast<Player *>(object);
        if(player)
        {
            
            if (madnessFilter == NULL) {
                madnessFilter = new LightFilterSpiceMadness();
            }
            player->getSightMap()->addFilter(madnessFilter);
        }
        
    }
}

void SpiceMadness::update()
{
    Effect::update();
    
    if(arc4random()%50==0)
    {
        LOG("You feel light headed.");
    }
}

void SpiceMadness::onAdded()
{
    Effect::onAdded();
   // LOG("You are temporarily less thirsty.");
}

void SpiceMadness::onRemoved()
{
    Effect::onRemoved();
    
    if(completeMadness)
    {
        Player *player = dynamic_cast<Player *>(object);
        if(player)
        {
            if (madnessFilter != NULL) {
                player->getSightMap()->removeFilter(madnessFilter);
            }
        }
    }
    
    LOG("You feel the effects of the spice wear off.");
}

void SpiceMadness::onFinished()
{
    Effect::onFinished();
    if(completeMadness)
    {
        // deal some damage, spice headache :D
        Player *player = dynamic_cast<Player *>(object);
        if(player)
        {
            int h = -(1+arc4random()%4);
            player->adjustHP(h);
            LOG("You feel a sharp and painful headache. <%d dmg>",h);
        }
    }
}