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

Ascii* LightFilterShadow::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    
    Point direction = Point(1, 1);
    
    DuneWorld* world = dynamic_cast<DuneWorld*>(map->getMap()->world);
    if (world == NULL) {
        return ascii;
    }
    
    switch (world->getTimeOfDay()) {
        case DayNightEvening:
            direction.X = 1;
            direction.Y = 0;
            break;
        case DayNightTiwilight:
            direction.X = 1;
            direction.Y = 0;
            break;
        case DayNightMidnight:
            break;
        case DayNightDawn:
            direction.X = 0;
            direction.Y = 1;
            break;
            break;
        case DayNightSunrise:
            direction.X = 0;
            direction.Y = 1;
            break;
        case DayNightMorning:
            direction.X = 1;
            direction.Y = 1;
            break;
        case DayNightMidday:
            direction.X = 1;
            direction.Y = 1;
            break;
        case DayNightAfternoon:
            direction.X = 1;
            direction.Y = 1;
            break;
            
        default:
            return ascii;
            break;
    }
    
    Tile* currentTile = map->tileAtPoint(worldPoint);
    WorldCoord coord;
    double darken = 0.025;
    
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
                        ascii->Background.darken(darken);
                        ascii->Foreground.darken(darken);
                    }
                }
            }
            else {
                //double val = 1.0/(comparisonTile->height - currentTile->height);
                if (comparisonTile->height < currentTile->height) {
                    for (int z = 0; z<weight; z++) {
                        ascii->Background.darken(darken);
                        ascii->Foreground.darken(darken);
                    }
                }
            }
        }
    }
    return ascii;
}