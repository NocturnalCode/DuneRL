//
//  RangeFilter.h
//  Roguelike
//
//  Created by Thomas Carey on 15/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_RangeFilter_h
#define Roguelike_RangeFilter_h


#include "LightFilter.h"
class RangeFilter : LightFilter {
protected:
    int maxRange;
    WorldCoord destinationPoint;
    bool shouldComplete;
    bool shouldCancel;
public:
    RangeFilter(WorldCoord destination);
    void setDestinationPoint(WorldCoord destination);
    WorldCoord getDestinationPoint();
    void setMaxRange(int range);
    int getMaxRange();
    bool handleEvents(SDL_Event *event);
    Ascii* apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii);
};

#endif
