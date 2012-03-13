//
//  LightFilterShadow.cpp
//  Roguelike
//
//  Created by Thomas Carey on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>

#include "LightFilterShadow.h"

#include "Ascii.h"
#include "Colour.h"
#include "Lightmap.h"
#include "Types.h"
#include "Point.h"
#include "Tile.h"
#include "DuneWorld.h"
#include "Map.h"

inline double abs(double val)
{
    return val > 0 ? val : -val;
}

double weighting(Point direction, int i, int j)
{
    if (i ==0 && j==0) {
        return 0;
    }
    int hits = 0;
    int excess = 1;
    if (direction.X + i == 0) {
        hits++;
        if (direction.Y == 0) {
            hits+=excess;
        }
    }
    if (direction.Y + j == 0) {
        hits++;
        if (direction.X == 0) {
            hits+=excess;
        }
    }
    if (direction.X - i == 0) {
        hits--;
        if (direction.Y == 0) {
            hits-=excess;
        }
    }
    if (direction.Y - j == 0) {
        hits--;
        if (direction.X == 0) {
            hits-=excess;
        }
    }
    
    return hits;
}


void darkenate(Colour *background, Colour *foreground, Tile* currentTile, Lightmap* map, WorldCoord worldPoint, Point direction)
{
    WorldCoord coord;
    double darken = 0.03;
    for (int i = -1; i<2; i++) {
        for (int j = -1; j < 2; j++) {
            coord.X = worldPoint.X - i;
            coord.Y = worldPoint.Y - j;
            Tile* comparisonTile = map->tileAtPoint(coord);
            
            //            Tile* less = NULL;
            //            Tile* more = NULL;
            //direction tells us which is more important
            double weight = weighting(direction, i, j);
            if (weight == 0) {
                continue;
            }
            
            if (weight < 0) {
                weight = abs(weight);
                if (comparisonTile->height > currentTile->height) {
                    //double val = 1.0/(comparisonTile->height - currentTile->height);
                    for (int z = 0; z<weight; z++) {
                        background->darken(darken);
                        foreground->darken(darken);
                    }
                }
            }
            else {
                //double val = 1.0/(comparisonTile->height - currentTile->height);
                if (comparisonTile->height < currentTile->height) {
                    for (int z = 0; z<weight; z++) {
                        background->darken(darken);
                        foreground->darken(darken);
                    }
                }
            }
        }
    }

}

Ascii* LightFilterShadow::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    
    Point direction = Point(1, 1);
    
    DuneWorld* world = dynamic_cast<DuneWorld*>(map->getMap()->world);
    if (world == NULL) {
        return ascii;
    }
    Point directionLast = Point(1,1);
    DayNight time = world->getTimeOfDay();
    
    time = (DayNight)(((int)3+(int)time)%DayNightCount);
    
    switch (time) {
        case DayNightEvening:
            direction.X = 1;
            direction.Y = -1;
            directionLast.X = 1;
            directionLast.Y = -1;
            break;
        case DayNightTiwilight:
            direction.X = -1;
            direction.Y = -1;
            directionLast.X = 1;
            directionLast.Y = -1;
            break;
        case DayNightMidnight:
            direction.X = -1;
            direction.Y = -1;
            directionLast.X = -1;
            directionLast.Y = -1;
            break;
        case DayNightDawn:
            direction.X = -1;
            direction.Y = 1;
            directionLast.X = -1;
            directionLast.Y = -1;
            break;
            break;
        case DayNightSunrise:
            direction.X = -1;
            direction.Y = 1;
            directionLast.X = -1;
            directionLast.Y = 1;
            break;
        case DayNightMorning:
            direction.X = 1;
            direction.Y = 1;
            directionLast.X = -1;
            directionLast.Y = 1;
            break;
        case DayNightMidday:
            direction.X = 1;
            direction.Y = 1;
            directionLast.X = 1;
            directionLast.Y = 1;
            break;
        case DayNightAfternoon:
            direction.X = 1;
            direction.Y = -1;
            directionLast.X = 1;
            directionLast.Y = 1;
            break;
            
        default:
            return ascii;
            break;
    }
    
    Tile* currentTile = map->tileAtPoint(worldPoint);
    
    Colour background = ascii->Background;
    Colour foreground = ascii->Foreground;
    darkenate(&background, &foreground, currentTile, map, worldPoint, direction);
    
    if (direction.X != directionLast.X || direction.Y != directionLast.Y) {
        //Then lets interpolate
        Colour background2 = ascii->Background;
        Colour foreground2 = ascii->Foreground;
        darkenate(&background2, &foreground2, currentTile, map, worldPoint, directionLast);
        double dayPartProgress = world->getDayPartProgress();
        background2.lerp(background, dayPartProgress);
        foreground2.lerp(foreground, dayPartProgress);
        ascii->Background = background2;
        ascii->Foreground = foreground2;
    }
    else {
        ascii->Background = background;
        ascii->Foreground = foreground;
    }
    
    return ascii;
}