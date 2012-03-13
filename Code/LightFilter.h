//
//  LightFilter.h
//  Roguelike
//
//  Created by Thomas Carey on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_LightFilter_h
#define Roguelike_LightFilter_h
class Ascii;
class Lightmap;
class Tile;

#include "Point.h"
#include "Types.h"

class LightFilter {
    
    
public:
    LightFilter();
    ~LightFilter();
    virtual Ascii *apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii); 
};

#endif
