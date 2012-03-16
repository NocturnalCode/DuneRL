//
//  Corpse.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Corpse.h"

#include "Monster.h"
#include "Stringer.h"

Corpse::Corpse(const Monster *monster) : Object(new Ascii(PERCENT,Colour::white(),Colour::clear()))
{
    name = stringFormat("%s's corpse",monster->name.c_str());
    description = monster->darticle  + "corpse of " + monster->iarticle + monster->name;
}