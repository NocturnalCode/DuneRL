//
//  Armoury.h
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef ARMOURY_INCLUDE_H
#define ARMOURY_INCLUDE_H

#include "Object.h"

class Armoury
{
protected:
    virtual void inspectNew(Object *object);
public:
    Armoury();
    
    template < class T >
    T *spawn()
    {
        T *newObject = new T();
        inspectNew(newObject);
        return newObject;
    };
    
    static Armoury *shared;
};

#endif /* ARMOURY_INCLUDE_H */
