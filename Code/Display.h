/*
 *  Display.h
 *  Roguelike
 *
 *  Created by Daniel Brooker on 4/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DISPLAY_H_INC
#define DISPLAY_H_INC 

#define TILE_HEIGHT 16
#define TILE_WIDTH 12

#include "Types.h"
#include "Rect.h"
class Ascii;

class Display
{
	public:
    virtual ~Display();

	virtual bool handleEvents(SDL_Event *event) { return false; };
	virtual void display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates) = 0;
	virtual void setParent(Display *parent) = 0;
	virtual Display* getParent() = 0;
	virtual Rect getFrame() = 0;
	virtual void setSelected(bool selected) {};
	virtual bool wantsEvents() {return false;};
	
	virtual void remove(Display *displayable) {};
	virtual void remove(Window *window) {};
    
    virtual void displayTile(float *texture, float *colour, float *background, Ascii ascii);
};

typedef std::list<Display*> Displays;

#endif /* DISPLAY_H_INC */