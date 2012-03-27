/*
 *  Roguelike.h
 *  Roguelike
 *
 *  Created by Daniel Brooker on 23/03/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */
 
#ifndef ROGUELIKE_H_INC
#define ROGUELIKE_H_INC 

#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#else
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#endif
#include "SDL_OpenGL.h"
#include "SDLWindow.h"
#include "Window.h"
#include "World.h"
#include "Image.h"
#include "Timer.h"
#include "ExitMenu.h"

#include <string>
#include <vector>
//#include <pair>

#include <iostream>
#include <fstream>

class Roguelike
{
protected:
    
    SDL_Event   event;
    bool        done;
    SDLWindow   *window;
    World		*world;
    SDL_TimerID timerDisplay,timerAnimate;
    static Uint32 Timerdisplay(Uint32 interval, void* param);
    static Uint32 Timeranimate(Uint32 interval, void* param);
    
    int			scale;
    int width, height;
    Sprite		*sprite; 
    Window		*rootWindow;
    ExitMenu	*menuWindow;
    Window		*character;
    
    virtual int init_window();
    virtual void init_world();
    
    virtual void showMenu();
    void worldProjection();
    int vertices;
    Image *logo;
    
    
    
public:
    Roguelike();
    ~Roguelike();
    int     poll();
    SDLWindow* getWindow(); 
    Window *getRootWindow();
    World *getWorld();
    Random *rnd;

    void log(std::string format, ...);

    static Roguelike *shared;
    static bool	dev; 
    
    //std::map<int, std::vector<std::string> > logs; // change to vector of pairs
    std::vector< std::pair<int, std::string> > logs;
    
    void playerEndedTurn();
    int getCurrentTurn();
};

#define LOG Roguelike::shared->log
#define RNG Roguelike::shared->rnd

#endif /* ROGUELIKE_H_INC */
