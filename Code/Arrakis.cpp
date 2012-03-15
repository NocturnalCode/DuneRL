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

Tile* Arrakis::generateTileAtCoord(int i, int j)
{
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
    double rockThreshold = minRock + (((double)(size-j-1)/(double)size)*(maxRock-minRock));
    double spiceThreshold = minSpice + ((((double)(j))/(double)size)*(maxSpice-minSpice));
    
    double h = heights->interpolatedAt(size, i, j);
    
    Colour foreground;
    Colour background;
    
    //h=h+0.5;
    if (h<0) {
        h = -h;
    }
    
    h = 0.5-h;
    if (h<0) {
        h = 0;
    }
    DuneTile *t = NULL;
    Object *o = NULL; 
    double r = rock->interpolatedAt(size, i, j);
    if(r > rockThreshold) 
    {
        std::vector<int> ascii;
        ascii.push_back(COMMA);
        ascii.push_back(QUOTE_SINGLE);
        ascii.push_back(0);
        
        foreground = Colour(1.0f,1.0f-(h*0.8f),0.0f);
        
        //                if(h < 0.215) 
        //                    background = col1;
        //                else if(h < 0.24) 
        //                    background = col2;
        //                else if(h < 0.255)
        //                    background = col3;
        //                else if(h < 0.275) 
        //                    background = col4;
        //                else if(h < 0.3)
        //                    background = col5;
        //                else if(h < 0.35)  
        //                    background = col6;
        //                else if(h < 0.4)
        //                    background = col7;
        //                else if(h < 0.45) 
        //                    background = col8;
        //                else if(h < 0.475)
        //                    background = col9;
        //                else if(h < 0.495)
        //                    background = colA;
        //                else
        //                    background = colB;
        
        //Rock the place
        //tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeRock,false);
        t = new DuneTile(i,j,GroundTypeRock,false);
        background = Colour(1.0f,0.1f,0.0f);
        o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
        t->height = h+r;
    }
    else 
    {
        std::vector<int> ascii;
        ascii.push_back(COMMA);
        ascii.push_back(QUOTE_SINGLE);
        ascii.push_back(0);
        
        foreground = Colour(1.0f,1.0f-(h*0.8f),0.0f);
        
        if(h < 0.215) 
            background = col1;
        else if(h < 0.24) 
            background = col2;
        else if(h < 0.255)
            background = col3;
        else if(h < 0.275) 
            background = col4;
        else if(h < 0.3)
            background = col5;
        else if(h < 0.35)  
            background = col6;
        else if(h < 0.4)
            background = col7;
        else if(h < 0.45) 
            background = col8;
        else if(h < 0.475)
            background = col9;
        else if(h < 0.495)
            background = colA;
        else
            background = colB;
        
        double s = spice->interpolatedAt(size, i, j);
        t = new DuneTile(i,j,GroundTypeSand,s>spiceThreshold);
        //tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeSand,s>spiceThreshold);
        o = new Object(new Ascii(0,foreground,background));
        
        t->height = h;
    }
    
    t->parent = this;
    t->Position = Point(i,j);
    
    o->setPassable(true);
    o->setTerrain(true);
    o->description = "the hot sand";
    t->addObject(o);
    
    return t;
}

void Arrakis::generate()
{
	//int i,j;
	
    //-- Generate the desert heightmap
    int octaves = 1;
    double persistence = 60;
    int perlinSize = 64;
	//Perlin heights(perlinSize, octaves,persistence);
    heights = new Perlin(perlinSize, octaves,persistence);

	
    //-- Generate polar ice in south pole, lower 5%
	
    //-- Generate the rock out croppings in the sothern hemisphere
    int octaves2 = 4;
    double persistence2 = 60;
    int perlinSize2 = 64;
	//Perlin rock(perlinSize2, octaves2,persistence2);
    rock = new Perlin(perlinSize2, octaves2,persistence2);
    ////We may want to place our rocks first... It seems best to place randomly and just grow the rock randomly
    
    minRock = 0.3;
    maxRock = 0.5;
    
    int octaves3 = 4;
    double persistence3 = 60;
    int perlinSize3 = 64;
	//Perlin spice(perlinSize3, octaves3,persistence3);
    spice = new Perlin(perlinSize3, octaves3,persistence3);
    ////We may want to place our rocks first... It seems best to place randomly and just grow the rock randomly
    
    minSpice = 0.3;
    maxSpice = 0.5;
    this->setVisibleRect(this->getVisibleRect());
    
    //-- Combine the above terrain maps
//    for(j=0;j<size;j++)
//    {
//		for(i=0;i< size;i++) 
//        {
//
//        }
//    }
    
//    for (int i = 0; i < 3; i++) {
//        
//        bool placementValid = false;
//        while (!placementValid) {
//            int width = 6+rand()%4;
//            int height = 4+rand()%6;
//            Rect placement = Rect(rand()%(size-width-1), rand()%((size/2)-height-1) + size/2, width, height);
//            bool test = true;
//            //Test that these tiles are valid
//            for (int i = placement.X; i<placement.X+width && test; i++) {
//                for (int j = placement.Y; j<placement.Y+height && test; j++) {
//                    
//                    DuneTile *tile = dynamic_cast<DuneTile*>(VVARRAYPP(i, j, tiles));
//                    if (tile) {
//                        if (tile->getGroundType() != GroundTypeSand || tile->getObjects()->size() != 1) {
//                            test = false;
//                            break;
//                        }
//                    }
//                    
//                }
//            }
//            
//            if (test) {
//                placementValid = true;
//                
//                createRoom(placement,Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//                
//            }
//            
//            
//        }
//        
//    }
    
    //-- Generate spice map
    
	//-- Generate the fortresses in the lower half of world
//	createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
    // and fortress mobs
    
    //-- Generate Camps
    // and camp mobs
    
    //-- Generate World Mobs
//    for(int i=0;i<90;i++)
//    {
//        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,0,1),Colour(0,0,0,0));
//        Monster *monster = new Monster(ascii);
//        monster->name = stringFormat("dune cat< %d>",i);
//        monster->speed = (Speed)(SpeedFast);
//        monster->setMaxHP((rand()%3)+2);
//        monster->behaviour = BehaviourAggressive | BehaviourFlees;
//        addObject(arc4random()%size,arc4random()%size,monster);
//        monsters.push_back(monster);
//        
//        //printf("<Spawned %s %dhp %s %s>\n",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
//    }
    
	printf("Generated map of size %dx%d\n",size,size);
}