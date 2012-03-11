/*
 *  SDLWindow.cpp
 *  SDL
 *
 *  Created by Daniel Brooker on 20/03/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "SDLWindow.h"

SDLWindow::SDLWindow(int width, int height, bool Fullscreen)
{
    windowBpp = 32;
    Width = width;
    Height = height;
    
    if( Fullscreen )
        makeFullscreen();
    else
        makeWindowed();
    
    if (screen == NULL) 
    {
        fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n", Width, Height, windowBpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	} 
    
    setTitle("A Quaffable Roguelike");
    return;
}

bool SDLWindow::handleEvents(SDL_Event *event)
{
    //If the window resized
/*
    if( event.type == SDL_VIDEORESIZE )
    {
        //Resize the screen
        screen = SDL_SetVideoMode( event.resize.w, event.resize.h, windowBpp, SDL_SWSURFACE | SDL_RESIZABLE );

        //If there's an error
        if( screen == NULL )
        {
            windowOK = false;
            return;
        }
    }
    //If enter was pressed
//    else*/ if( ( event->type == SDL_KEYDOWN ) && ( event->key.keysym.sym == SDLK_RETURN ) )
//    {
//        //Turn fullscreen on/off
//		if(fullscreen)
//			makeWindowed();
//		else
//			makeFullscreen();
//		return true;
//    }
    //If the window focus changed
	if( event->type == SDL_ACTIVEEVENT )
    {
        //If the window was iconified or restored
        if( event->active.state & SDL_APPACTIVE )
        {
            //If the application is no longer active
            if( event->active.gain == 0 )
            {
                //SDL_WM_SetCaption( "Window Event Test: Iconified", NULL );
            }
            else
            {
                //SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the keyboard focus
        else if( event->active.state & SDL_APPINPUTFOCUS )
        {
            //If the application lost keyboard focus
            if( event->active.gain == 0 )
            {
                //SDL_WM_SetCaption( "Window Event Test: Keyboard focus lost", NULL );
            }
            else
            {
                //SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the mouse focus
        else if( event->active.state & SDL_APPMOUSEFOCUS )
        {
            //If the application lost mouse focus
            if( event->active.gain == 0 )
            {
                //SDL_WM_SetCaption( "Window Event Test: Mouse Focus Lost", NULL );
            }
            else
            {
                //SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
    }
    //If the window's screen has been altered
    else if( event->type == SDL_VIDEOEXPOSE )
    {
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            //If there's an error
//            windowOK = false;
            return true;
        }
    }
	return false;
}

void SDLWindow::makeFullscreen()
{
    screen = SDL_SetVideoMode(  Width, Height, windowBpp, /*SDL_SWSURFACE |*/ SDL_OPENGL | SDL_RESIZABLE | SDL_FULLSCREEN );
    fullscreen = true;
    return;
}

void SDLWindow::makeWindowed()
{
    screen = SDL_SetVideoMode( Width, Height, windowBpp, /*SDL_SWSURFACE |*/ SDL_OPENGL );
    fullscreen = false;
    return;
}

void SDLWindow::setTitle(const char* title)
{
    SDL_WM_SetCaption( title, NULL );
    return;
}

SDL_Surface* SDLWindow::getScreen()
{
    return screen;
}