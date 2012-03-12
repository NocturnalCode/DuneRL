/*
 *  Roguelike.cpp
 *  Roguelike
 *
 *  Created by Daniel Brooker on 23/03/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "Roguelike.h"
#include "Map.h"

#include <string>

typedef enum {
	RoguelikeDisplay=1,
	RoguelikeAnimate=2
} UserEvents;

Roguelike *Roguelike::shared = NULL;
bool Roguelike::dev = false;

Roguelike::Roguelike()
{
    menuWindow = NULL;
    Roguelike::shared = this;
}

Roguelike::~Roguelike()
{
    SDL_RemoveTimer(timerDisplay);
	SDL_RemoveTimer(timerAnimate);
    SDL_Quit();
}

SDLWindow* Roguelike::getWindow()
{
    return window;
}

void Roguelike::log(std::string format, ...)
{
    char *buffer;
    va_list args;
    va_start(args, format);
    vasprintf(&buffer,format.c_str(), args);
    va_end(args);
    
    std::string entry = std::string(buffer);
    int turn = world->getTurn();
    
    printf("[%d]LOG: %s\n",turn,entry.c_str());
    
    std::string turnLog = logs[turn];
    if(turnLog.empty())
    {
        logs[turn] = entry;
//        printf("new log entry\n");
    }
    else
    {
        logs[turn] = turnLog + std::string("% ") + entry;
//        printf("adding to log\n");
    }
}

int Roguelike::init_window()
{
    fprintf(stderr,"Init\n");

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
    
	width = 640;
	height = 480;
	
	window = new SDLWindow(width,height,false);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	worldProjection();
    
    if( glGetError() != GL_NO_ERROR ) 
    {
        fprintf(stderr,"Failed.\n");
        return 1; 
    }
	
    timerDisplay = SDL_AddTimer(1000/50, Timerdisplay, this);
	timerAnimate = SDL_AddTimer(1000/2.5, Timeranimate, this); 
	SDL_EnableKeyRepeat(25, 50);
	
    fprintf(stderr,"Loading...Done.\n");
    return 0;
}

void Roguelike::worldProjection()
{
    glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity();
    glOrtho( 0, window->getScreen()->w, window->getScreen()->h, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW ); 
    glLoadIdentity();
}

void Roguelike::init_world()
{
	rnd = new Random(42);

	sprite = new Sprite("Roguelike.app/Contents/Resources/tileset.png",16);
    world = new World();
}

int Roguelike::poll()
{
    done = false;
	
	// Calculate fps
	int frame = 0;
	Timer fps;  
	Timer update;
	update.start();
	fps.start();
	
	while ( !done ) 
    {
		/* Check for events */
		while ( !done && SDL_WaitEvent(&event) ) 
        {
			if(window->handleEvents(&event))
				continue;
			if(rootWindow->eventDelegate->handleEvents(&event))
				continue;
			// check for window events then switch
			switch (event.type)
            {
                case SDL_USEREVENT:
					// clear
					switch(event.user.code)
					{
						case RoguelikeAnimate:
							world->getMap()->updateAscii();
							break;
						case RoguelikeDisplay:
							worldProjection();
							glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
							glLoadIdentity();

							/// draw window
							rootWindow->display();
							
							glFlush();
							SDL_GL_SwapBuffers();
							frame++;
							if(DEV)
							{
								if( update.get_ticks() > 1000 ) 
								{ 
									char caption[15];
									snprintf(caption, 15, "%.2f FPS",floor(frame / ( fps.get_ticks() / 1000.f)));
									rootWindow->getLeftLabel()->setString(caption);
									update.start(); 
								}
							}
							else
							{
								rootWindow->getLeftLabel()->setString("");
							}
							break; 
					}
					break;
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
							//done = true;
							showMenu();
							break;
                        default:
                            break;
					}
					break;
				case SDL_QUIT:
					done = true;
					break;
				default:  
					break;
			}
		}
	}
    return 0;
}

void Roguelike::showMenu()
{
	if(!menuWindow->isOpen)
	{
		rootWindow->add(menuWindow);
		menuWindow->open();
	}
	else
	{
		//rootWindow->remove(menuWindow);
		menuWindow->close();
        
	}
    
}

Uint32 Roguelike::Timerdisplay(Uint32 interval, void* param)
{
    // Create a user event to call the game loop.
    SDL_Event event;
    
    event.type = SDL_USEREVENT;
	event.user.code =  1;
    event.user.data1 = 0;
    event.user.data2 = 0;
    
    SDL_PushEvent(&event);
    
    return interval;
}

Uint32 Roguelike::Timeranimate(Uint32 interval, void* param)
{
    // Create a user event to call the game loop.
    SDL_Event event;
    
    event.type = SDL_USEREVENT;
	event.user.code =  2;
    event.user.data1 = 0;
    event.user.data2 = 0;
    
    SDL_PushEvent(&event);
    
    return interval;
}