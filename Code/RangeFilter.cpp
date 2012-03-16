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
#include "Window.h"


RangeFilter::RangeFilter(LocalCoord destination) : LightFilter()/*,Display()*/
{
    maxRange = -1;
    destinationPoint = destination;
    shouldComplete = NO;
    shouldCancel = NO;
}

void RangeFilter::setDestinationPoint(LocalCoord destination)
{
    //bresham line function to find valid points
    linePoints.clear();
    double angle = atan2(destination.Y, destination.X);//(double)(destinationPoint.Y)/(double)(destinationPoint.X);
    
    //double magnitude = sqrt((destinationPoint.Y*destinationPoint.Y) + (destinationPoint.X+destinationPoint.X));
    
    if (abs(destination.Y) > abs(destination.X)) {
        //then go up Y
        int direction = destination.Y<0 ? 1 : -1;
        
        
        for (int i = 0; i<abs(destination.Y); i++) {
            double actual_j = i*direction;
            
            //just need the xcoord for the current actual_i value
            //y = mx+c
            //x = (y-c)/m
            //o = a*tan(ø)
            double actual_i = actual_j/tan(angle);
            //shade in point ((int)actual_i, (int)actual_j)
            linePoints.insert(std::pair<int, int>((int)actual_i,(int)actual_j));
        }
    }
    else {
        int direction = destination.X<0 ? 1 : -1;
        //then go up X
        for (int i = 0; i<abs(destination.Y); i++) {
            double actual_i = i*direction;
            
            //just need the xcoord for the current actual_i value
            //y = mx+c
            //x = (y-c)/m
            //o = a*tan(ø)
            double actual_j = actual_i*tan(angle);
            linePoints.insert(std::pair<int, int>((int)actual_i,(int)actual_j));
            //shade in point ((int)actual_i, (int)actual_j)
        }
    }

    this->destinationPoint = destination;
}

LocalCoord RangeFilter::getDestinationPoint()
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
    
    
    if (shouldCancel || shouldComplete) {
        World* world = (map->getMap()->world);
        Window *window = dynamic_cast<Window*>(world->getParent());
        if (window != NULL) {
            window->eventDelegate = world;
        }
        
        return ascii;
    }
    
    //destination point is probable going to have to be a local coord
    WorldCoord pos = map->getPosition();
    //lets assume worldpoint is relative to pos
    LocalCoord local = pos-worldPoint;
    
    if (linePoints.find(std::pair<int, int>(local.X,local.Y)) != linePoints.end()) {
        //render this 
        ascii->Background = Colour::yellow();
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



