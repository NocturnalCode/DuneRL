/*
 *  SDLWindow.h
 *  SDL
 *
 *  Created by Daniel Brooker on 20/03/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif

#ifndef SDLWINDOW_H_INC
#define SDLWINDOW_H_INC 
 
#define DEFAULT_WIDTH	800
#define DEFAULT_HEIGHT	600
 
class SDLWindow
{
    private:
        bool        fullscreen;

        Uint8       windowBpp;
        SDL_Surface* screen;

    public:
		int         Width;
        int         Height;
		
        SDLWindow(int Width, int Height, bool Fullscreen);
        bool handleEvents(SDL_Event *event);
        void makeFullscreen();
        void makeWindowed();
        void setTitle(const char* title);
        SDL_Surface* getScreen();
};

#endif /* SDLWINDOW_H_INC */

