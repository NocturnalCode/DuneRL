/*
 *  Tile.cpp
 *  Roguelike
 *
 *  Created by Daniel on 6/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Map.h"
#include "Tile.h"
#include "Point.h"

Tile::Tile()
{
	Tile(-1,-1);
}

Tile::Tile(int i, int j)
{
	lastAscii = NULL;
	objects = new Objects();
	_flags.visited = NO;
	_flags.passable  = YES;
	_flags.transparent = YES;
	Position = Point(i,j);
}

Tile::~Tile()
{
    delete objects;
    lastAscii = NULL;
    parent = NULL;
}

void Tile::addObject(Object *object)
{
	object->setParent(this);
	objects->push_back(object);
	
	if(object->_flags.passable==NO)
		_flags.passable = NO;
		
	if(object->_flags.transparent==NO)
		_flags.transparent = NO;
}

void Tile::removeObject(Object *object)
{
	object->setParent(NULL);
	objects->remove(object);
	
	bool passable = true,transparent = true;
	foreachp(Objects,o,objects)
	{
		if((*o)->_flags.passable==NO)
			passable = false;
		
		if((*o)->_flags.transparent==NO)
			transparent = false;
	}
	_flags.passable = passable ? YES : NO ;
	_flags.transparent = transparent ? YES : NO ;
}

Ascii *Tile::getTopAscii(bool visible)
{
	Ascii *ascii = NULL;
	if(visible)
	{
		if(objects->size() > 0)
        {   
            Object *object = objects->back();
			ascii = object->getAscii();

            if(ascii->backgroundInherits)
            {
                Colour colour;
                foreachp(Objects,o,objects)
                {
                    //we want to find the last object that doesn't have a clear background colour
                    //this is an over simplification.. Alpha is effectively On or Off, not continuous
                    
                    if ((*o)->getAscii()->backgroundInherits != true) {
                        colour = (*o)->getAscii()->Background;
                    }
                }
                
                //Ascii *low = objects->front()->getAscii();
                ascii->Background = colour;//low->Background;
            }
        }
		_flags.visited = YES;
		lastAscii = ascii;
	}
	else if(_flags.visited)
	{
		ascii = lastAscii;
	}
	
	return ascii;
}

std::string Tile::description()
{
    int i=0;
    std::string desc = "";
    rforeachp(Objects,o,objects)
    {
        Object *object = (*o);
        Monster *monster = dynamic_cast<Monster *>(object);
        if(monster != NULL)
        {
            desc += (*o)->description + " stand";
        }
        else
        {
            desc += "on " + (*o)->description;
            if(object->terrain())
                break; // don't describe under the terrain
        }
        
        i++;
        if(i!=objects->size())
            desc += " ";
    }
    return desc;
}

Object *Tile::getTopObject()
{
    if(objects->size() > 0)
        return objects->back();
    else
        return NULL;
}
