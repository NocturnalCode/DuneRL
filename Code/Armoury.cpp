//
//  Armoury.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Armoury.h"

Armoury *Armoury::shared = NULL;

Armoury::Armoury() 
{
    shared = this;
}

void Armoury::inspectNew(Object *object)
{
    
}

void Armoury::inspect(void *o)
{
    inspectNew(static_cast<Object *>(o));
}

