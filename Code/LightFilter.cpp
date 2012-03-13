//
//  LightFilter.cpp
//  Roguelike
//
//  Created by Thomas Carey on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>
#include "LightFilter.h"
#include "Lightmap.h"
#include "Tile.h"
#include "Ascii.h"


LightFilter::LightFilter()
{
    
}

LightFilter::~LightFilter()
{
    
}

Ascii* LightFilter::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    return ascii;
}