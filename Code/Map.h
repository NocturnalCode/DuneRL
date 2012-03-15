/*
 *  Map.h
 *  Roguelike
 *
 *  Created by Daniel on 24/04/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */



#ifndef MAP_H_INC
#define MAP_H_INC 

#include "SDL_OpenGL.h" 
#include "Object.h"

#include "Types.h"
#include "Tile.h"

#include "Rect.h"
#include "World.h"
#include "Perlin.h"

typedef enum {
	MapTypeNoTile,
	MapTypeFullTile,
	MapTypeWorldTile,
    // Keep SpeedCount at bottom
    MapTypeCount
} MapType;

class Monster;

class Map
{
private:
    Rect	visibleRect;
    Rect mapRect;
    
    
protected:
    
    float *tex,*col,*bgCol;
    //Tile **tiles;
    
    std::vector<std::vector<Tile*>*> *tiles;
    
    Monster *player;
    void displayTile(float *texture, float *colour,float *backgroundColour, Tile *tile, Monster *monster);
    bool mapFlippednessChanged;
    
    Perlin *heights;
public:
    World	*world;
    Monsters monsters;
    Objects	 objects;
    
    int size;
    MapType maptype;
    bool mapFlipped;
    Map(unsigned size);
    ~Map();
    virtual void generate();
    virtual Tile* generateTileAtCoord(int i, int j);
    virtual void createRoom(Rect rect,Ascii floor);
    
    void setVisibleRect(Rect visiRect);
    Rect getVisibleRect();
    
    void update(Speed turnSpeed);
    void updateAscii();
    
    Tile *getTile(WorldCoord point);
    WorldCoord convertWorldCoordRelativeToMapCoord(WorldCoord point);
    
    
    
    bool adjustPlayer(int i, int j);
    
    void setPlayer(Monster *player);
    Monster *getPlayer();
    
    // arrays to display
    void setTexturePointer(float *texurePointer);
    void setColourPointer(float *colourPointer);
    void setBackgroundColourPointer(float *bgColourPointer);
    
    // Display
    void display();
    
    void addObject(int x, int y,Object *object);
    void removeObject(Object *object);
    void moveObject(Object *object, int i, int j);
    bool checkMove(Object *object, int i, int j);
    
    bool checkCombat(Monster *monster, int i, int j);
    bool checkAction(Object *object, int i, int j);
    
    bool getTransparent(int x, int y);
    
    bool lineOfSight(Point a,Point b);
    Objects getVisibleObjects(Object *orgin,int range);
    Objects getVisibleMonsters(Object *orgin,int range);
};

#endif /* MAP_H_INC  */