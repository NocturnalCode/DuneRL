//
//  DuneTile.h
//  Roguelike
//
//  Created by Thomas Carey on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef Roguelike_DuneTile_h
#define Roguelike_DuneTile_h
#include "Tile.h"

typedef enum {
    GroundTypeSand,
    GroundTypeIce,
    GroundTypeRock,
    GroundTypeCount
} GroundType;

class DuneTile : public Tile {
protected:
    bool spiceGenerator;
    //bool mobSpawner; // could be useful?
    int turnLastSeen;
    GroundType groundType;
    
public:
    DuneTile(int i, int j, GroundType type, bool spiceGenerator);
    int getTurnLastSeen();
    void setTurnLastSeen(int val);
    bool isSpiceGenerator();
    GroundType getGroundType();
    virtual void update(Speed updateSpeed, int turnNumber);
};

#endif
