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

Ascii* LightFilterDayNightCycle::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //we want to change the ascii now...
    ascii->Background.darken(0.5);
    ascii->Foreground.darken(0.5);
    return ascii;
}