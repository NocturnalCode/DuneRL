//
//  Arrakis.h
//  Roguelike
//
//  Created by Daniel Brooker on 12/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef ARRAKIS_H_INC
#define ARRAKIS_H_INC

#include "Map.h"
#include "Tile.h"

class Arrakis: public Map
{
protected:
    Perlin *rock;
    Perlin *spice;
    Perlin *heights;
    double minRock;
    double maxRock;
    double minSpice;
    double maxSpice;
public:
    Arrakis(unsigned size);
    
    virtual void generate();
    Tile* generateTileAtCoord(int i, int j);
};

#endif /* ARRAKIS_H_INC */
