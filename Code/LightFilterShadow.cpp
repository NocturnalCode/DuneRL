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
    if (direction.X + i == 0) {
        hits++;
        if (direction.Y == 0) {
            hits+=2;
        }
    }
    if (direction.Y + j == 0) {
        hits++;
        if (direction.X == 0) {
            hits+=2;
        }
    }
    if (direction.X - i == 0) {
        hits--;
        if (direction.Y == 0) {
            hits-=2;
        }
    }
    if (direction.Y - j == 0) {
        hits--;
        if (direction.X == 0) {
            hits-=2;
        }
    }
    
    return hits;
}

Ascii* LightFilterShadow::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    
    Point direction = Point(1, 1);
    
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
                    for (int z = 0; z<weight; z++) {
                        ascii->Background.darken(darken);
                        ascii->Foreground.darken(darken);
                    }
                }
            }
            else {
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