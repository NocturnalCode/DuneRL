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
#include "Roguelike.h"


RangeFilter::RangeFilter(LocalCoord destination) : LightFilter(),Display()
{
    maxRange = -1;
    destinationPoint = destination;
    shouldComplete = NO;
    shouldCancel = NO;
}

void RangeFilter::setDestinationPoint(LocalCoord destination)
{
    //bresham line function to find valid points
    double magnitude = sqrt((destination.Y*destination.Y) + (destination.X*destination.X));
    if (magnitude>maxRange) {
        return;
    }
    linePoints.clear();
    //double angle = atan2(destination.Y, destination.X);//(double)(destinationPoint.Y)/(double)(destinationPoint.X);
    shouldComplete = NO;
    shouldCancel = NO;
    //
    int x1 = 0;
    int y1 = 0;
    int x2 = -destination.X;
    int y2 = -destination.Y;
    
    Point end;
    
    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x(x2 - x1);
    signed char ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
    
    int delta_y(y2 - y1);
    signed char iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    
    //plot(x1, y1);
    linePoints.insert(std::pair<int, int>(x1,y1));
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        
        while (x1 != x2)
        {
            if (error >= 0)
            {
                if (error || (ix > 0))
                {
                    y1 += iy;
                    error -= delta_x;
                }
                // else do nothing
            }
            // else do nothing
            
            x1 += ix;
            error += delta_y;
            
            linePoints.insert(std::pair<int, int>(x1,y1));
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        
        while (y1 != y2)
        {
            if (error >= 0)
            {
                if (error || (iy > 0))
                {
                    x1 += ix;
                    error -= delta_y;
                }
                // else do nothing
            }
            // else do nothing
            
            y1 += iy;
            error += delta_x;
            
            linePoints.insert(std::pair<int, int>(x1,y1));
        }
    }

//    if (abs(destination.Y) > abs(destination.X)) {
//        //then go up Y
//        int direction = destination.Y<0 ? 1 : -1;
//        
//        
//        for (int i = 0; i<abs(destination.Y); i++) {
//            double actual_j = i*direction;
//            
//            //just need the xcoord for the current actual_i value
//            //y = mx+c
//            //x = (y-c)/m
//            //o = a*tan(ø)
//            double actual_i = actual_j/tan(angle);
//            //shade in point ((int)actual_i, (int)actual_j)
//            linePoints.insert(std::pair<int, int>((int)actual_i,(int)actual_j));
//        }
//    }
//    else {
//        int direction = destination.X<0 ? 1 : -1;
//        //then go up X
//        for (int i = 0; i<abs(destination.Y); i++) {
//            double actual_i = i*direction;
//            
//            //just need the xcoord for the current actual_i value
//            //y = mx+c
//            //x = (y-c)/m
//            //o = a*tan(ø)
//            double actual_j = actual_i*tan(angle);
//            linePoints.insert(std::pair<int, int>((int)actual_i,(int)actual_j));
//            //shade in point ((int)actual_i, (int)actual_j)
//        }
//    }

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
        Roguelike *like = Roguelike::shared;
        like->getRootWindow()->eventDelegate = (map->getMap()->world);
        
        //World* world = ;
        //Window *window = dynamic_cast<Window*>(world->getParent());
        //if (window != NULL) {
        //    window->eventDelegate = world;
        //}
        //map->removeFilter(this);
        
        if(shouldComplete)
        {
        
            WorldCoord impact = map->getPosition() + destinationPoint;
            /// Tom get it to check the bresham line
            
            
            // check tile
            Tile *tile = map->getMap()->getTile(impact);
            Object *target = NULL;
            
            if(tile)
            {
                target = tile->getTopObject();
            }
            
            if(target)
            {
                map->getMap()->getPlayer()->attack(target);
            }
            else 
            {
                // shot nothing, maybe rand spawn a bullet
            }
        }
        shouldCancel = NO;
        shouldComplete = NO;
        
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
                    if (Roguelike::shared->getWorld()->getMap()->mapFlipped) {
                        this->setDestinationPoint(Point(destinationPoint.X, destinationPoint.Y+1));
                    }
                    else {
                        this->setDestinationPoint(Point(destinationPoint.X, destinationPoint.Y-1));
                    }
                    
                }
                    break;
                case SDLK_DOWN:
                {
                    if (Roguelike::shared->getWorld()->getMap()->mapFlipped) {
                        this->setDestinationPoint(Point(destinationPoint.X, destinationPoint.Y-1));
                    }
                    else {
                        this->setDestinationPoint(Point(destinationPoint.X, destinationPoint.Y+1));
                    }
                }
                    break;
                case SDLK_LEFT: 
                {
                    this->setDestinationPoint(Point(destinationPoint.X-1, destinationPoint.Y));
                }
                    break;
                case SDLK_RIGHT:
                {
                    this->setDestinationPoint(Point(destinationPoint.X+1, destinationPoint.Y));
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

void RangeFilter::display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates)
{
    Roguelike::shared->getWorld()->display(texCoordinates, colCoordinates, bgColCoordinates);
}
void RangeFilter::setParent(Display *parent)
{
    Roguelike::shared->getWorld()->setParent(parent);
}
Display* RangeFilter::getParent()
{
    return Roguelike::shared->getWorld()->getParent();
}
Rect RangeFilter::getFrame()
{
    return Roguelike::shared->getWorld()->getFrame();
}



