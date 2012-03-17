//
//  DuneArmoury.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "DuneArmoury.h"
#include "Corpse.h"
#include "Blood.h"

DuneArmoury::DuneArmoury() : Armoury()
{
    
}

void DuneArmoury::inspectNew(Object *object)
{
    Corpse *corpse = dynamic_cast<Corpse *>(object);
    Blood *blood = dynamic_cast<Blood *>(object);
    if(corpse || blood) // this doesn't work :(
    {
        object->_flags.consumable = YES;
        return;
    }
}

