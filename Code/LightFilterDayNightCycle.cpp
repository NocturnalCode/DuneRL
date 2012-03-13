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

Ascii* LightFilterDayNightCycle::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    Colour colour = ascii->Background;
    ascii->Background.destaturate();//(0.5);
    ascii->Background.lerp(colour, 0.3);
    
    
    double viewRadius = map->getRadius();
    viewRadius = 2*(viewRadius*viewRadius);
    Point position = map->getPosition();
    LocalCoord local = map->world2local(worldPoint);
    
    int X = local.X-map->getRadius();//worldPoint.X - position.X;//local.X;
    int Y = local.Y-map->getRadius();//worldPoint.Y - position.Y;//local.Y;
    double distance = (X*X)+(Y*Y);
    
    distance = distance/(viewRadius*0.15);
    if (distance > 1.0) {
        distance = 1.0;
    }
    ascii->Background.darken(distance);
    ascii->Foreground.darken(distance);
    return ascii;
}