//
//  DuneWorld.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "DuneWorld.h"
#include "DuneRL.h"

DuneWorld::DuneWorld() : World()
{
    dayNight = DayNightMidday;
    dayNightTick = 0;
}

void DuneWorld::updateWorld()
{
    World::updateWorld();

    dayNightTick++;
    if(dayNightTick > TURNS_IN_A_DAY_PART)
    {
        dayNight = (DayNight)((dayNight+1)%DayNightCount);
        dayNightTick = 0;
        
        switch (dayNight) {
            case DayNightMorning:
                LOG("It is now morning");
                break;
            case DayNightMidday:
                LOG("It is now mid-day");
                break;
            case DayNightEvening:
                LOG("It is getting darker");
                break;
            case DayNightMidnight:
                LOG("It is new very dark");
                break;
            default:
                break;
        }
    }
    
    //printf("turn %d",getTurn());
}