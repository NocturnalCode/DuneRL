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

class Arrakis: public Map
{
protected:
    virtual void createRoom(Rect rect,Ascii floor);
public:
    Arrakis(unsigned size);
    
    virtual void generate();
};

#endif /* ARRAKIS_H_INC */
