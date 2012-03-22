/*
 *  DuneRL.cpp
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#include "DuneRL.h"

#include <map>

#include "Stringer.h"
#include "LabelValue.h"
#include "Player.h"

#include "DuneWorld.h"
#include "Map.h"

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_OpenGL.h"
#include "SDLWindow.h"
#include "Window.h"
#include "ActionLog.h"

#include "Image.h"
#include "Timer.h"
#include "ExitMenu.h"
#include "WinMenu.h"
#include "Player.h"
#include "Arrakis.h"

#include "StartMenu.h"

DuneRL *DuneRL::shared = NULL;

DuneRL::DuneRL()
{
    shared = this;
    
	init_window();
    window->setTitle("DuneRL 7DRL 2012, Quaffable");
    
	init_world();
	
	menuWindow = new ExitMenu(Rect(256-24,128,140+32,64+24));
	
	rootWindow = new Window(Rect(0,0,width,height));
	rootWindow->delegate = world;
	rootWindow->eventDelegate = world;
	rootWindow->texture = sprite;
    rootWindow->borderStyle = Border_Double;
	rootWindow->getCentreLabel()->setString("DuneRL");
	rootWindow->getRightLabel()->setString("v1.0.1");
	
	character = new Window(Rect(16,24,140+32,65+12));
	character->borderStyle = Border_Single;
	character->getLeftLabel()->setString(player->name);
	character->getLeftLabel()->setColour(Colour::white());
	
	Label *familyLabel = new Label(player->family);
	familyLabel->setFrame(Rect(16,18,100,40));
	familyLabel->setColour(Colour::white());
	character->add(familyLabel);
	
    CallBack<Player, std::string> *getHealth = new CallBack<Player, std::string>(player,&Player::hpDescription);
    LabelValue<std::string,Player> *health = new LabelValue<std::string,Player>("",getHealth);
	health->setFrame(Rect(16,27,100,40));
	health->setColour(Colour(0,1,0));
	character->add(health);
    
    CallBack<Player, std::string> *getWater = new CallBack<Player, std::string>(player,&Player::waterDescription);
    LabelValue<std::string,Player> *water = new LabelValue<std::string,Player>("",getWater);
	water->setFrame(Rect(16,36,100,40));
	water->setColour(Colour::white());
	character->add(water);
//    
    CallBack<Player, std::string> *getSpice = new CallBack<Player, std::string>(player,&Player::spiceDescription);
    LabelValue<std::string,Player> *spice = new LabelValue<std::string,Player>("",getSpice);
	spice->setFrame(Rect(16,36+18,100,40));
	spice->setColour(Colour::white());
	character->add(spice);
	
	rootWindow->add(character);
    
    CallBack<Player, std::string> *getUnderfoot = new CallBack<Player, std::string>(player,&Player::underfootDescription);
    LabelValue<std::string,Player> *underfoot = new LabelValue<std::string,Player>("",getUnderfoot);
	underfoot->setFrame(Rect(16,462,640-8,40));
	underfoot->setColour(Colour(1,1,1));
	rootWindow->add(underfoot);
    
    // action log
    actionLog = new ActionLog(Rect(16,462-60-12,640-32,60));
    actionLog->borderStyle = Border_None;
    rootWindow->add(actionLog);
    
    // start menu
    StartMenu *start = new StartMenu(Rect((600-492)/2+12,128,492+12,64+48),player);
    rootWindow->add(start);
    start->open();
    
    // inventory
    inventory =  new Inventory(Rect(600-256-24,24,256+24+12,48), player);
}

DuneRL::~DuneRL()
{
    if(player)
        delete player;
}

void DuneRL::init_world()
{
	int worldSize = 800;
	
	rnd =  new Random(arc4random());
	
	sprite = new Sprite("DuneRL.app/Contents/Resources/tileset.png",16);
    world = new DuneWorld();
    
    Map *map = new Arrakis(worldSize);
    map->generate();
    world->setMap(map);
	
	player = new Player();
    
    world->getMap()->addObject(100,100,player);
	world->getMap()->setPlayer(player);
    world->getMap()->monsters.push_back(player);

    player->calculateSight();
}

void DuneRL::deathMenu()
{
    dmenu = new DeathMenu(Rect(256-64,128,140+128,64+24),player);
    rootWindow->add(dmenu);
    dmenu->open();
}

void DuneRL::winMenu()
{
    WinMenu *wmenu = new WinMenu(Rect(256-64,128,140+128,64+24),player);
    rootWindow->add(wmenu);
    wmenu->open();
}

void DuneRL::inventoryMenu()
{
	if(!inventory->isOpen)
	{
		rootWindow->add(inventory);
		inventory->open();
	}
	else
	{
		inventory->close();
	}
}