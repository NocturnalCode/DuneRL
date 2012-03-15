//
//  RangeFilter.cpp
//  Roguelike
//
//  Created by Thomas Carey on 15/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>

#include "RangeFilter.h"
#include "Lightmap.h"
#include "Map.h"
#include "World.h"

RangeFilter::RangeFilter(WorldCoord destination) : LightFilter()
{
    maxRange = -1;
    destinationPoint = destination;
    shouldComplete = NO;
    shouldCancel = NO;
}

void RangeFilter::setDestinationPoint(WorldCoord destination)
{
    this->destinationPoint = destination;
}

WorldCoord RangeFilter::getDestinationPoint()
{
    return this->destinationPoint;
}

void RangeFilter::setMaxRange(int range)
{
    this->maxRange = range;
}

int RangeFilter::getMaxRange()
{
    return this->maxRange;
}

Ascii* RangeFilter::apply(Lightmap* map, WorldCoord worldPoint, Ascii* ascii)
{
    
    //basically draw a line to that point and stop at the first non-transparent object
    World* world = (map->getMap()->world);
    
    if (shouldCancel || shouldComplete) {
        
    }
    
    return ascii;
}

bool RangeFilter::handleEvents(SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_KEYDOWN:
        {
			switch( event->key.keysym.sym )
            {
                case SDLK_UP:	
                {
                    destinationPoint.Y--;
                }
                    break;
                case SDLK_DOWN:
                {
                    destinationPoint.Y++;
                }
                    break;
                case SDLK_LEFT: 
                {
                    destinationPoint.X--;
                }
                    break;
                case SDLK_RIGHT:
                {
                    destinationPoint.X++;
                }
                    break;
                case SDLK_RETURN:
                    shouldComplete = YES;
                    break;
                case SDLK_ESCAPE:
                    shouldCancel = YES;
                    break;
                default:
                    return false;
            }
        }
			break;
		default:
			return false;
	}
	return true;
}



