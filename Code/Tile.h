/*
 *  Tile.h
 *  Roguelike
 *
 *  Created by Daniel on 6/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef TILE_H_INC
#define TILE_H_INC 

class Map;

#include "Point.h"
#include "Ascii.h"
#include "Types.h"

typedef struct {
	unsigned visited:1;
	unsigned passable:1;
	unsigned transparent:1;
	unsigned _reserved:29;
} TileFlags;

class Tile 
{
private:
    Ascii *lastAscii;
    Objects *objects;
public:
    Map *parent;
    Point Position;
    TileFlags _flags;
    
    Tile();
    Tile(int i, int j);
    ~Tile();
    Ascii *getTopAscii(bool visible);
    Ascii *getTerainAscii(bool visible);

    void addObject(Object *object);
    void removeObject(Object *object);

    Object *getTopObject();

    std::string description();
};

#endif /* TILE_H_INC  */