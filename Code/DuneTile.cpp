//
//  DuneTile.cpp
//  Roguelike
//
//  Created by Thomas Carey on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>
#include "DuneTile.h"

DuneTile::DuneTile(int i, int j, GroundType type, bool isSpiceGenerator) : Tile(i,j)
{
    turnLastSeen = 0;
    this->spiceGenerator = isSpiceGenerator;
    this->groundType = type;
}

int DuneTile::getTurnLastSeen()
{
    return this->turnLastSeen;
}

void DuneTile::setTurnLastSeen(int val)
{
    this->turnLastSeen = val;
}

bool DuneTile::isSpiceGenerator()
{
    return this->spiceGenerator;
}

GroundType DuneTile::getGroundType()
{
    return this->groundType;
}