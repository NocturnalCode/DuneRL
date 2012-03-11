/*
 *  DuneRL.cpp
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#include "DuneRL.h"

#include "Stringer.h"
#include "LabelValue.h"
#include "Player.h"

#include "World.h"
#include "Map.h"

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_OpenGL.h"
#include "SDLWindow.h"
#include "Window.h"
//#include "World.h"
#include "Image.h"
#include "Timer.h"
#include "ExitMenu.h"
#include "Player.h"

DuneRL::DuneRL()
{
	init_window();
    window->setTitle("DuneRL 7DRL 2012, Quaffable");
    
	init_world();
	
	menuWindow = new ExitMenu(Rect(256-24,128,140+32,64+24));
	
	rootWindow = new Window(Rect(0,0,width,height));
	rootWindow->delegate = world;
	rootWindow->eventDelegate = world;
	rootWindow->texture = sprite;
	rootWindow->getCentreLabel()->setString("DuneRL");
	rootWindow->getRightLabel()->setString("v1.0");
	
	character = new Window(Rect(16,24,140+32,32+16));
	character->borderStyle = Border_Double;
	character->getLeftLabel()->setString("Leto Atreides");
	character->getLeftLabel()->setColour(Colour::white());
	
	Label *familyLabel = new Label("House Atreides");
	familyLabel->setFrame(Rect(16,18,100,40));
	familyLabel->setColour(Colour::blue());
	character->add(familyLabel);
	
    CallBack<Player, std::string> *getHealth = new CallBack<Player, std::string>(player,&Player::hpDescription);
    LabelValue<std::string,Player> *health = new LabelValue<std::string,Player>("",getHealth);
	health->setFrame(Rect(16,18+12,100,40));
	health->setColour(Colour(0,1,0));
	character->add(health);
	
	rootWindow->add(character);
}

DuneRL::~DuneRL()
{
    if(player)
        delete player;
}

void DuneRL::init_world()
{
	int worldSize = 200;
	
	rnd =  new Random(42);
	
	sprite = new Sprite("DuneRL.app/Contents/Resources/tileset.png",16);
    world = new World();
    
    world->setMap(new Map(worldSize));
	
	player = new Player();
    
    world->getMap()->addObject(12,12,player);
	world->getMap()->setPlayer(player);
    world->getMap()->monsters.push_back(player);
    
    world->getMap()->createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	world->getMap()->createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
    
    
    for(int i=0;i<1;i++)
    {
        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,1,1),Colour(0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("Cat< %d>",i);
        monster->speed = (Speed)(rand()%SpeedCount);
        monster->setMaxHP(rand()%4);
        monster->behaviour = 1<<(rand()%BehaviourCount);
        world->getMap()->addObject(rand()%20,rand()%20,monster);
        world->getMap()->monsters.push_back(monster);
        
        LOG("Spawned %s %dhp %s %s",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    
    player->calculateSight();
}