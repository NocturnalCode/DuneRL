//
//  DuneArmoury.h
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef DUNEARMOURY_INCLUDE_H
#define DUNEARMOURY_INCLUDE_H

#include "Armoury.h"

class DuneArmoury : public Armoury
{
protected:
    virtual void inspectNew(Object *object);
public:
    DuneArmoury();
};

#endif /* DUNEARMOURY_INCLUDE_H */
