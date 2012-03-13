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


Ascii* LightFilterShadow::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    
    
    Tile* currentTile = map->tileAtPoint(worldPoint);
    WorldCoord coord;
    coord.X = worldPoint.X - 2;
    coord.Y = worldPoint.Y - 2;
    
    for (int i = 0; i<3; i++) {
        for (int j = 0; j < 3; j++) {
            
        }
    }
    
    Tile* comparisonTile = map->tileAtPoint(coord);
    if (comparisonTile->height > currentTile->height) {
        //ok, we know we have to darken it, but its not clear by how much
        ascii->Background.darken(0.05);
        ascii->Foreground.darken(0.05);
    }
    coord.X = worldPoint.X - 2;
    coord.Y = worldPoint.Y - 1;
    comparisonTile = map->tileAtPoint(coord);
    if (comparisonTile->height > currentTile->height) {
        //ok, we know we have to darken it, but its not clear by how much
        ascii->Background.darken(0.05);
        ascii->Foreground.darken(0.05);
    }
    coord.X = worldPoint.X - 1;
    coord.Y = worldPoint.Y - 2;
    comparisonTile = map->tileAtPoint(coord);
    if (comparisonTile->height > currentTile->height) {
        //ok, we know we have to darken it, but its not clear by how much
        ascii->Background.darken(0.05);
        ascii->Foreground.darken(0.05);
    }
    return ascii;
}