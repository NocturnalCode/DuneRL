//
//  DuneTile.cpp
//  Roguelike
//
//  Created by Thomas Carey on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <iostream>
#include "DuneTile.h"
#include "Object.h"
#include "Spice.h"

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

void DuneTile::update(Speed updateSpeed, int turnNumber)
{
    Tile::update(updateSpeed, turnNumber);
    int turnDifference = turnNumber - this->getTurnLastSeen();
    if (turnDifference > 1 && spiceGenerator) {
        //Then lets consider adding spice
        int val = rand()%1000;
        if (val < (0.05*(double)turnDifference)) {
            
            //Then check for a spice
            bool noSpice = YES;
            
            foreachp(Objects, o, this->getObjects())
            {
                Object *object = (*o);
                Spice *spice = dynamic_cast<Spice*>(object);
                if (spice != NULL) {
                    noSpice = NO;
                    break;
                }
            }
            
            if (noSpice) {
                Spice *spice = new Spice();
                this->addLiquid(spice);
            }
        }
    }
    
    this->setTurnLastSeen(turnNumber);
}