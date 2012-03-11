//
//  Arrakis.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 12/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Arrakis.h"
#include "Perlin.h"
#include "Stringer.h"
#include "DuneRL.h"

Arrakis::Arrakis(unsigned size) : Map(size)
{
    
}

void Arrakis::generate()
{
	int i,j;
	
	Perlin heights(size, 3,1.0);
	
	for(j=0;j<size;j++)
    {
		for(i=0;i< size;i++) 
        {
			double h = heights.at(i,j) + 1;
			std::vector<int> ascii;
			ascii.push_back(COMMA);
			ascii.push_back(QUOTE_SINGLE);
			ascii.push_back(0);
			
			Colour foreground(0.1f,(float)((int)(i*h)%4)*0.2,0.f);
			Colour background(Colour::yellow());
			
			Object *o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
			
			tiles[ARRAY2D(i,j,size)]->Position = Point(i,j);
			o->setPassable(true);
			addObject(i,j,o);
        }
    }
	
	/*
     Generation Stages
     - - - - - - - - -
     Rock
     Ground
     Plants
     Cities
     Items
     Creeps
     Treasure
     - - - - - - - - -
     */
	
	createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
    
    for(int i=0;i<1;i++)
    {
        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,1,1),Colour(0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("Cat< %d>",i);
        monster->speed = (Speed)(rand()%SpeedCount);
        monster->setMaxHP(rand()%4);
        monster->behaviour = 1<<(rand()%BehaviourCount);
        addObject(rand()%20,rand()%20,monster);
        monsters.push_back(monster);
        
        LOG("Spawned %s %dhp %s %s",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    
	printf("Generated map of size %dx%d\n",size,size);
}