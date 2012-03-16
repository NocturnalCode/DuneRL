//
//  RangeFilter.h
//  Roguelike
//
//  Created by Thomas Carey on 15/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_RangeFilter_h
#define Roguelike_RangeFilter_h
#include "Display.h"
#include "LightFilter.h"
#include "Point.h"
#include <set>

class RangeFilter : public LightFilter/*,Display*/ {
protected:
    int maxRange;
    LocalCoord destinationPoint;
    bool shouldComplete;
    bool shouldCancel;
    std::set<std::pair<int, int> > linePoints;
public:
    RangeFilter(LocalCoord destination);
    void setDestinationPoint(LocalCoord destination);
    LocalCoord getDestinationPoint();
    void setMaxRange(int range);
    int getMaxRange();
    bool handleEvents(SDL_Event *event);
    Ascii* apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii);
};

#endif
