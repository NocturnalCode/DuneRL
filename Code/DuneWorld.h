//
//  DuneWorld.h
//  Roguelike
//
//  Created by Daniel Brooker on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef DUNEWORLD_INCLUDE_H
#define DUNEWORLD_INCLUDE_H

#include "World.h"

typedef enum {
    DayNightSunrise,
    DayNightMorning,
    DayNightMidday,
    DayNightAfternoon,
    DayNightEvening,
    DayNightTiwilight,
    DayNightMidnight,
    DayNightDawn,
    DayNightCount
} DayNight;

#define TURNS_IN_A_DAY 200
#define TURNS_IN_A_DAY_PART TURNS_IN_A_DAY/DayNightCount

class DuneWorld : public World
{
protected:
    int dayNightTick;
    DayNight dayNight;
    
    virtual void updateWorld();
    
public:
    DuneWorld();
};

#endif /* DUNEWORLD_INCLUDE_H */
