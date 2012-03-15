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
#include "DuneTile.h"

Arrakis::Arrakis(unsigned size) : Map(size)
{
    
}

#define DUNE1 0x917d47
#define DUNE2 0x9c874d 
#define DUNE3 0xa28c4e
#define DUNE4 0xae9754
#define DUNE5 0xc5a95f
#define DUNE6 0xccb161
#define DUNE7 0xdcbe69
#define DUNE8 0xe5c56e
#define DUNEB 0xfeda78
#define DUNE9 0xefce73
#define DUNEA 0xfeda79

void Arrakis::generate()
{
	int i,j;
	
    //-- Generate the desert heightmap
    int octaves = 1;
    double persistence = 60;
    int perlinSize = 64;
	Perlin heights(perlinSize, octaves,persistence);
    
    Colour col1(DUNE1);
    Colour col2(DUNE2);
    Colour col3(DUNE3);
    Colour col4(DUNE4);
    Colour col5(DUNE5);
    Colour col6(DUNE6);
    Colour col7(DUNE7);
    Colour col8(DUNE8);
    Colour col9(DUNE9);
    Colour colA(DUNEA);
    Colour colB(DUNEB);
	
    //-- Generate polar ice in south pole, lower 5%
	
    //-- Generate the rock out croppings in the sothern hemisphere
    int octaves2 = 4;
    double persistence2 = 60;
    int perlinSize2 = 64;
	Perlin rock(perlinSize2, octaves2,persistence2);
    ////We may want to place our rocks first... It seems best to place randomly and just grow the rock randomly
    
    double minRock = 0.3;
    double maxRock = 0.5;
    
    int octaves3 = 4;
    double persistence3 = 60;
    int perlinSize3 = 64;
	Perlin spice(perlinSize3, octaves3,persistence3);
    ////We may want to place our rocks first... It seems best to place randomly and just grow the rock randomly
    
    double minSpice = 0.3;
    double maxSpice = 0.5;
    
    
    //-- Combine the above terrain maps
    for(j=0;j<size;j++)
    {
		for(i=0;i< size;i++) 
        {
            
//            int idx = i*perlinSize/size;
//            int jdx = j*perlinSize/size;
            
            //y = j
            double rockThreshold = minRock + (((double)j/(double)size)*(maxRock-minRock));
            double spiceThreshold = minSpice + ((((double)(size-j-1))/(double)size)*(maxSpice-minSpice));
            
            
			double h = heights.interpolatedAt(size, i, j);
            
            //h=h+0.5;
            if (h<0) {
                h = -h;
            }
            
            h = 0.5-h;
            if (h<0) {
                h = 0;
            }
            
            
            
//            h = h / ((double)octaves * persistence);
//            if (h>6) {
//                h = 1;
//            }
//            if (h<0.5) {
//                h= 0;
//            }
//            else {
//                h = 1;
//            }
            
            
//            h *= 20.0;
//            h = h-(int)h;
            
			std::vector<int> ascii;
			ascii.push_back(COMMA);
			ascii.push_back(QUOTE_SINGLE);
			ascii.push_back(0);
			
            //h*
            
           // printf("perlinValue: %f\n", h);
            
            // lowest
            Colour foreground;
            Colour background;
            
            if(h < 0.215) 
            {
                background = col1;
            }
            else if(h < 0.24) 
            {
                background = col2;
            }
            else if(h < 0.255)
            {
                background = col3;
            }
            else if(h < 0.275) 
            {
                background = col4;
            }
            else if(h < 0.3)
            {
                background = col5;
            }
            else if(h < 0.35)  
            {
                background = col6;
            }
            else if(h < 0.4)
            {
                background = col7;
            }
            else if(h < 0.45) 
            {
                background = col8;
            }
            else if(h < 0.475)
            {
                background = col9;
            }
            else if(h < 0.495)
            {
                background = colA;
            }
            else
            {
                background = colB;
            }
            
			foreground = Colour(1.0f,1.0f-(h*0.8f),0.0f);
            //Colour background(1.0f,1.0f-h,0.0f);
            
//            if ((i<2 || j<2 || j>size-3 || i>size-3)&&DEV) {
//                background = Colour::blue();
//            }
			
            Object *o = NULL; 
            double r = rock.interpolatedAt(size, i, j);
            if (r>rockThreshold) {
                //Rock the place
                tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeRock,false);
                background = Colour(1.0f,0.1f,0.0f);
                o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
                tiles[ARRAY2D(i,j,size)]->height = h+r;
            }
            else {
                
                double s = spice.interpolatedAt(size, i, j);
                if (s>spiceThreshold) {
                    tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeSand,true);
                    foreground = Colour::red();
                    o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
                }
                else {
                    tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeSand,false);
                    o = new Object(new Ascii(0,foreground,background));
                }
                
                tiles[ARRAY2D(i,j,size)]->height = h;
            }
            
			
			
            
            
			tiles[ARRAY2D(i,j,size)]->parent = this;
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
    for(int i=0;i<90;i++)
    {
        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,0,1),Colour(0,0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("dune cat< %d>",i);
        monster->speed = (Speed)(SpeedFast);
        monster->setMaxHP((rand()%3)+2);
        monster->behaviour = BehaviourAggressive | BehaviourFlees;
        addObject(arc4random()%size,arc4random()%size,monster);
        monsters.push_back(monster);
        
        //printf("<Spawned %s %dhp %s %s>\n",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    
	printf("Generated map of size %dx%d\n",size,size);
}