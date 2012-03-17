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

Corpse::Corpse() : Object(new Ascii(PERCENT,Colour::white(),Colour::clear()))
{
    _flags.consumable = YES;
}