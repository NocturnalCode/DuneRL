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
#include "Arrakis.h"

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
    rootWindow->borderStyle = Border_Double;
	rootWindow->getCentreLabel()->setString("DuneRL");
	rootWindow->getRightLabel()->setString("v1.0");
	
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
    
    CallBack<DuneRL, std::string> *getlog = new CallBack<DuneRL, std::string>(this,&DuneRL::getTurnLog);
    LabelValue<std::string,DuneRL> *log = new LabelValue<std::string,DuneRL>("",getlog);
	log->setFrame(Rect(16,450,640-8,40));
	log->setColour(Colour(1,1,1));
	rootWindow->add(log);
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
    
    Map *map = new Arrakis(worldSize);
    map->generate();
    world->setMap(map);
	
	player = new Player();
    
    world->getMap()->addObject(12,12,player);
	world->getMap()->setPlayer(player);
    world->getMap()->monsters.push_back(player);

    player->calculateSight();
}

std::string DuneRL::getTurnLog()
{
    if(logs.size() <= 0)
        return "<empty>";
    return logs[logs.size()-1];
}
