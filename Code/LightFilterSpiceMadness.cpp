//
//  LightFilterSpiceMadness.cpp
//  Roguelike
//
//  Created by Thomas Carey on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>

#include "LightFilterSpiceMadness.h"
#include "Colour.h"
#include "Ascii.h"

Ascii* LightFilterSpiceMadness::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    //basic effect is that we simply turn the filter on set a little more blue on the ascii
    Colour blue = Colour::cyan();
    
    ascii->Background.lerp(blue, 0.2);
    ascii->Foreground.lerp(blue, 0.5);
    return ascii;
}