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
	
    //-- Generate the desert heightmap
	Perlin heights(size, 3,1.0);
	
    //-- Generate polar ice in south pole, lower 5%
	
    //-- Generate the rock out croppings in the sothern hemisphere
    
    //-- Combine the above terrain maps
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
            o->setTerrain(true);
            o->description = "the hot sand";
			addObject(i,j,o);
        }
    }
    
    //-- Generate spice map
    
	//-- Generate the fortresses in the lower half of world
	createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
	createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
    // and fortress mobs
    
    //-- Generate Camps
    // and camp mobs
    
    //-- Generate World Mobs
    for(int i=0;i<1;i++)
    {
        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,0,1),Colour(0,0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("dune cat< %d>",i);
        monster->speed = (Speed)(rand()%SpeedCount);
        monster->setMaxHP(rand()%4);
        monster->behaviour = 1<<(rand()%BehaviourCount);
        addObject(rand()%20,rand()%20,monster);
        monsters.push_back(monster);
        
        LOG("<Spawned %s %dhp %s %s>",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    
	printf("Generated map of size %dx%d\n",size,size);
}