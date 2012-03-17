//
//  LightFilterSpiceMadness.h
//  Roguelike
//
//  Created by Thomas Carey on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_LightFilterSpiceMadness_h
#define Roguelike_LightFilterSpiceMadness_h

#include "LightFilter.h"

class LightFilterSpiceMadness : public LightFilter {
    
public:
    Ascii* apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii);
};

#endif
