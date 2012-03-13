//
//  LightFilterDayNightCycle.h
//  Roguelike
//
//  Created by Thomas Carey on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_LightFilterDayNightCycle_h
#define Roguelike_LightFilterDayNightCycle_h

#include "LightFilter.h"

class LightFilterDayNightCycle : public LightFilter {
    
public:
    Ascii* apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii);
};

#endif
