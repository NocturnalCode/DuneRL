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
#include "Rect.h"
#include "Point.h"
#include "Ranged.h"

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

#define ROCK1 0x552c18
#define ROCK2 0x763d21
#define ROCK3 0x8c4827
#define ROCK4 0xac5930
#define ROCK5 0xc76738

void Arrakis::createRoom(Rect rect,Ascii floor)
{
	Object* o;
	for(int i=rect.X;i<rect.X+rect.Width-1;i++)
	{
		for(int j=rect.Y;j<rect.Y+rect.Height-1;j++)
		{
			o = new Object(new Ascii(floor));
			o->setPassable(true);
			addObject(i,j,o);
            Tile *t =  getTile(Point(i,j));
            t->height = 1;
            
            DuneTile *dt = dynamic_cast<DuneTile *>(t);
            if(dt)
                dt->setGroundType(GroundTypeFortress);
		}
	}
	
	//top left
	o = new Object(new Ascii(BLOCK+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X,rect.Y,o);
	//top right
	o = new Object(new Ascii(BLOCK+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X+rect.Width-1,rect.Y,o);
    
	//bottom left
	o = new Object(new Ascii(BLOCK+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X,rect.Y+rect.Height-1,o);
	//bottom right
	o = new Object(new Ascii(BLOCK+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X+rect.Width-1,rect.Y+rect.Height-1,o);
	
	for(int j=rect.Y+1;j<rect.Y+rect.Height-1;j++)
	{
		o = new Object(new Ascii(LINE_VERTICAL_DOUBLE +16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
		o->setPassable(false);
		o->setTransparent(false);
		addObject(rect.X,j,o);
		addObject(rect.X+rect.Width-1,j,o);
	}
	
	for(int i=rect.X+1;i<rect.X+rect.Width-1;i++)
	{
		if(i==(int)(rect.X+(rect.Width/2)))
		{
			o = new Object(new Ascii(JOINT_DOUBLE_CENTER_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(1.0,0.5,0))); // a door
            
		}
		else
		{
			o = new Object(new Ascii(LINE_HORIZONTAL_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
			o->setPassable(false);
		}
		o->setTransparent(false);
		addObject(i,rect.Y,o);
        Tile *t = getTile(Point(i,rect.Y));
        t->height = 1;
		addObject(i,rect.Y+rect.Height-1,o);
        t = getTile(Point(i,rect.Y+rect.Height-1));
        t->height = 1;
	}
	
	printf("Creating room: %d %d %d %d\n",rect.X,rect.Y,rect.Width,rect.Height);
}


void Arrakis::generate()
{
	int i,j;
	
    //-- Generate the desert heightmap
    int octaves = 1;
    double persistence = 60;
    int perlinSize = 64;
	Perlin heights(perlinSize, octaves,persistence);
    
    Colour sand1(DUNE1);
    Colour sand2(DUNE2);
    Colour sand3(DUNE3);
    Colour sand4(DUNE4);
    Colour sand5(DUNE5);
    Colour sand6(DUNE6);
    Colour sand7(DUNE7);
    Colour sand8(DUNE8);
    Colour sand9(DUNE9);
    Colour sandA(DUNEA);
    Colour sandB(DUNEB);
    
    Colour rock1(DUNE1);
    Colour rock2(DUNE2);
    Colour rock3(DUNE3);
    Colour rock4(DUNE4);
    Colour rock5(DUNE5);
	
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
            double rockThreshold = minRock + (((double)(size-j-1)/(double)size)*(maxRock-minRock));
            double spiceThreshold = minSpice + ((((double)(j))/(double)size)*(maxSpice-minSpice));
            
			double h = heights.interpolatedAt(size, i, j);
            
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
			
            Object *o = NULL; 
            double r = rock.interpolatedAt(size, i, j);
            if(r > rockThreshold) 
            {
                std::vector<int> ascii;
                ascii.push_back(LETTER_o+16);
               // ascii.push_back(LETTER_o);
                ascii.push_back(0);
                ascii.push_back(0);
                ascii.push_back(0);
                ascii.push_back(0);
                
                foreground = Colour(1.0f,1.0f-(h*0.8f),0.0f);
                
                if(r < 0.2) 
                    background = rock1;
                else if(r < 0.3)
                    background = rock2;
                else if(r < 0.4)
                    background = rock3;
                else if(r < 0.5) 
                    background = rock4;
                else
                    background = rock5;
                
                //Rock the place
                tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeRock,false);
                background = Colour(1.0f,0.1f,0.0f);
                o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
                o->description = "rock";
                tiles[ARRAY2D(i,j,size)]->height = h+r;
            }
            else 
            {
                std::vector<int> ascii;
                ascii.push_back(0);
                ascii.push_back(0);
                ascii.push_back(0);
                ascii.push_back(0);
                ascii.push_back(0);
                
                if(h < 0.215) 
                    background = sand1;
                else if(h < 0.24) 
                    background = sand2;
                else if(h < 0.255)
                    background = sand3;
                else if(h < 0.275) 
                    background = sand4;
                else if(h < 0.3)
                    background = sand5;
                else if(h < 0.35)  
                    background = sand6;
                else if(h < 0.4)
                    background = sand7;
                else if(h < 0.45) 
                    background = sand8;
                else if(h < 0.475)
                    background = sand9;
                else if(h < 0.495)
                    background = sandA;
                else
                    background = sandB;
                
                foreground = background;
                foreground.darken();
                
                if(h < 0.25f)
                {
                    ascii.push_back(TILDE+16);
                }
                else
                {
                    //ascii.push_back(TILDE+16);
                    ascii.push_back(TILDE_DOUBLE);
                }
                
                double s = spice.interpolatedAt(size, i, j);
                
                tiles[ARRAY2D(i,j,size)] = new DuneTile(i,j,GroundTypeSand,s>spiceThreshold);
                o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
                
                tiles[ARRAY2D(i,j,size)]->height = h;
                
                o->description = "the hot sand";
            }
            
			tiles[ARRAY2D(i,j,size)]->parent = this;
			tiles[ARRAY2D(i,j,size)]->Position = Point(i,j);
            
			o->setPassable(true);
            o->setTerrain(true);
            
			addObject(i,j,o);
        }
    }
    
    //-- Generate the fortresses in the lower half of world
    for (int i = 0; i < 3; i++) {
        
        bool placementValid = false;
        while (!placementValid) {
            int width = 6+rand()%4;
            int height = 4+rand()%6;
            Rect placement = Rect(rand()%(size-width-1), rand()%((size/2)-height-1) + size/2, width, height);
            bool test = true;
            //Test that these tiles are valid
            for (int i = placement.X; i<placement.X+width && test; i++) {
                for (int j = placement.Y; j<placement.Y+height && test; j++) {
                    
                    DuneTile *tile = dynamic_cast<DuneTile*>(tiles[ARRAY2D(i,j,size)]);
                    if (tile) {
                        if (tile->getGroundType() != GroundTypeSand || tile->getObjects()->size() != 1) {
                            test = false;
                            break;
                        }
                    }
                    
                }
            }
            
            if (test) {
                placementValid = true;
                
                createRoom(placement,Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
                
                for(int j=0;j<5;j++)
                {
                    Ascii *ascii = new Ascii(SMILIE,Colour(0,0,1),Colour(0,0,0,0));
                    Monster *monster = new Monster(ascii);
                    monster->speed = (Speed)(SpeedNormal);
                    monster->setMaxHP((rand()%3)+2);
                    monster->behaviour = BehaviourAggressive;
                    
                    // make some random mobs
                    switch (i) {
                        case 0: // fremen
                            monster->name = stringFormat("fremen< %d>",j);
                            monster->getAscii()->Foreground = Colour::yellow();
                            monster->oid = 32;
                            monster->setMaxHP((rand()%5)+3);
                            break;
                        case 1: // atreides
                        {
                            monster->name = stringFormat("atreides< %d>",j);
                            monster->getAscii()->Foreground = Colour::blue();
                            monster->oid = 42;
                            
                            Ranged *ranged = new Ranged();
                            monster->addObjectToInventory(ranged);
                            monster->equip(ranged);
                        }
                            break;
                        case 2: // harkonnen
                        {
                            monster->name = stringFormat("harkonnen< %d>",j);
                            monster->getAscii()->Foreground = Colour::black();
                            monster->oid = 24;
                            
                            Ranged *ranged = new Ranged();
                            monster->addObjectToInventory(ranged);
                            monster->equip(ranged);
                        }
                            break;
                        default:
                            break;
                    }
                    
                    placement.inset(-10, -10);
                    
                    Rect rect = placement;
                    Point p(rect.X + (rand() % rect.Width),rect.Y + (rand() % rect.Height));
                    
                    addObject(arc4random()%size,arc4random()%size,monster);
                    monsters.push_back(monster);
                }
            }
            
            
        }
        
    }
    
    //-- Generate Camps
    // and camp mobs
    int faction = arc4random()%3;
    Point camp((rand() % size),(rand() % size));
    Rect campsite = Rect(camp.X,camp.Y,20,20);
    
    for(int j=0;j<5;j++)
    {
        Ascii *ascii = new Ascii(SMILIE,Colour(0,0,1),Colour(0,0,0,0));
        Monster *monster = new Monster(ascii);
        monster->speed = (Speed)(SpeedNormal);
        monster->setMaxHP((rand()%3)+2);
        monster->behaviour = BehaviourAggressive;
        
        // make some random mobs
        switch (faction) {
            case 0: // fremen
                monster->name = stringFormat("fremen< %d>",j);
                monster->getAscii()->Foreground = Colour::yellow();
                monster->oid = 32;
                break;
            case 1: // atreides
            {
                monster->name = stringFormat("atreides< %d>",j);
                monster->getAscii()->Foreground = Colour::blue();
                monster->oid = 42;
                
                Ranged *ranged = new Ranged();
                monster->addObjectToInventory(ranged);
                monster->equip(ranged);
            }
                break;
            case 2: // harkonnen
            {
                monster->name = stringFormat("harkonnen< %d>",j);
                monster->getAscii()->Foreground = Colour::black();
                monster->oid = 24;
                
                Ranged *ranged = new Ranged();
                monster->addObjectToInventory(ranged);
                monster->equip(ranged);
            }   
                break;
            default:
                break;
        }
        
        Rect rect = campsite;
        Point p(rect.X + (rand() % rect.Width),rect.Y + (rand() % rect.Height));
        
        addObject(arc4random()%size,arc4random()%size,monster);
        monsters.push_back(monster);
    }

    
    //-- Generate World Mobs
    for(int i=0;i<60;i++)
    {
        Ascii *ascii = new Ascii(LETTER_c+16,Colour(0,0,1),Colour(0,0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("dune cat< %d>",i);
        monster->speed = (Speed)(SpeedFast);
        monster->setMaxHP((rand()%3)+2);
        monster->behaviour = BehaviourAggressive | BehaviourFlees;
        monster->oid = 222;
        addObject(arc4random()%size,arc4random()%size,monster);
        monsters.push_back(monster);
        //printf("<Spawned %s %dhp %s %s>\n",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    for(int i=0;i<100;i++)
    {
        Ascii *ascii = new Ascii(LETTER_m+16,Colour(0,0,1),Colour(0,0,0,0));
        Monster *monster = new Monster(ascii);
        monster->name = stringFormat("Muad'Dib< %d>",i);
        monster->speed = (Speed)(SpeedFast);
        monster->setMaxHP(1);
        monster->behaviour = BehaviourTimid | BehaviourFlees;
        monster->oid = 111;
        monster->sight = 8;
        addObject(arc4random()%size,arc4random()%size,monster);
        monsters.push_back(monster);
        //printf("<Spawned %s %dhp %s %s>\n",monster->name.c_str(),monster->getMaxHP(),stringForSpeed(monster->speed).c_str(),stringForBehaviour(monster->behaviour).c_str());
    }
    
	printf("Generated map of size %dx%d\n",size,size);
}