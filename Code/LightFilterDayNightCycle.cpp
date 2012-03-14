//
//  LightFilterDayNightCycle.cpp
//  Roguelike
//
//  Created by Thomas Carey on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>
#include "LightFilterDayNightCycle.h"
#include "Ascii.h"
#include "Colour.h"
#include "Lightmap.h"
#include "Types.h"
#include "Point.h"
#include "Tile.h"
#include "DuneWorld.h"
#include "Map.h"

Ascii* LightFilterDayNightCycle::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    
    DuneWorld* world = dynamic_cast<DuneWorld*>(map->getMap()->world);
    if (world == NULL) {
        return ascii;
    }
    double viewDist = 0.15;
    double desaturationFactor = 0.3;
    double desaturationLast = 1.0;
    double viewDistLast = 1.0;
    switch (world->getTimeOfDay()) {
        case DayNightEvening:
            viewDist = 0.25;
            viewDistLast = 1.0;
            desaturationFactor = 0.5;
            desaturationLast = 1.0;
            break;
        case DayNightTiwilight:
            viewDist = 0.20;
            viewDistLast = 0.25;
            desaturationFactor = 0.4;
            desaturationLast = 0.5;
            break;
        case DayNightMidnight:
            viewDist = 0.10;
            viewDistLast = 0.20;
            desaturationFactor = 0.3;
            desaturationLast = 0.4;
            break;
        case DayNightDawn:
            viewDist = 0.25;
            viewDistLast = 0.1;
            desaturationFactor = 0.5;
            desaturationLast = 0.3;
            break;
        case DayNightSunrise:
            viewDist = 1;
            viewDistLast = 0.25;
            desaturationFactor = 1;
            desaturationLast = 0.5;
            break;
        case DayNightMorning:
        case DayNightMidday:
        case DayNightAfternoon:
        
        default:
            return ascii;
            break;
    }
    double dayPartProgress = world->getDayPartProgress();
    viewDist = viewDistLast + dayPartProgress*(viewDist-viewDistLast);
    desaturationFactor = desaturationLast + dayPartProgress*(desaturationFactor-desaturationLast);
    //we want to change the ascii now...
    Colour colour = ascii->Background;
    ascii->Background.destaturate();//(0.5);
    ascii->Background.lerp(colour, desaturationFactor);
    
    
    double viewRadius = map->getRadius();
    viewRadius = 2*(viewRadius*viewRadius);
    Point position = map->getPosition();
    LocalCoord local = map->world2local(worldPoint);
    
    int X = local.X-map->getRadius();//worldPoint.X - position.X;//local.X;
    int Y = local.Y-map->getRadius();//worldPoint.Y - position.Y;//local.Y;
    double distance = (X*X)+(Y*Y);
    
    distance = distance/(viewRadius*viewDist);
    if (distance > 1.0) {
        distance = 1.0;
    }
    ascii->Background.darken(distance);
    ascii->Foreground.darken(distance);
    return ascii;
}