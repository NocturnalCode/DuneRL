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

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_OpenGL.h"
#include "SDLWindow.h"
#include "Window.h"
#include "World.h"
#include "Image.h"
#include "Timer.h"
#include "ExitMenu.h"
#include <string>
#include <vector>
#include <map>

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
    
        std::map<int, std::vector<std::string> > logs;

    public:
        Roguelike();
		~Roguelike();
        int     poll();
        SDLWindow* getWindow(); 
    
        Random *rnd;
		
        void log(std::string format, ...);
        static Roguelike *shared;
		static bool	dev; 

};

#define LOG Roguelike::shared->log
#define RNG Roguelike::shared->rnd

#endif /* ROGUELIKE_H_INC */
