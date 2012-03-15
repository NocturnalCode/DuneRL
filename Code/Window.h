/*
 *  Window.h
 *  Roguelike
 *
 *  Created by Daniel on 30/03/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef WINDOW_H_INC
#define WINDOW_H_INC 

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_OpenGL.h"
#include "Display.h"
#include "Label.h"
#include "Sprite.h"
#include <string>

typedef enum {
	Border_None,
	Border_Single,
	Border_Double,
	Border_Block
} Border;

class Window : public Display
{
private:
    float	*vertexCoordinates;
    float	*texCoordinates;
    float	*colCoordinates;
    float	*bgColCoordinates;
    int		vertices;

    

protected:
    Rect	rect;
    int		scale;
    Label	centreLabel,leftLabel,rightLabel;
    Windows windows;
    Displays displays;
    Display *parent;
    
    void	setup();
    void    reset();
    void	setupVertexCoordinates();
    void	border(float *texCoordinates, float *colCoordinates, float *bgColCoordinates);
    
public:
    Window(Rect rect);
    virtual ~Window();
    virtual void display();
    
    virtual void add(Display *displayable);
    virtual void add(Window *window);
    
    virtual void remove(Display *displayable);
    virtual void remove(Window *window);
    
    Label* getCentreLabel();
    Label* getLeftLabel();
    Label* getRightLabel();
    
    Colour borderColour;
    Border borderStyle;
    Sprite	*texture;
    Display *eventDelegate;
    Display *delegate;
    bool background;
    
    virtual void setParent(Display *parent);
    virtual Display* getParent();
    
    virtual Rect getFrame();
    
    virtual void display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates);
};

#endif /* WINDOW_H_INC */