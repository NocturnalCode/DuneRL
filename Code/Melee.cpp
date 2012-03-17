//
//  Melee.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Melee.h"

Melee::Melee() : Object(new Ascii(BRACKET_LEFT_CURVED,Colour::white(), Colour::clear()))
{
    _flags.wieldable = YES;
    name = "melee weapon";
}

Damages Melee::getMeleeDamages()
{
    Damages dmgs;
    dmgs.push_back(Damage(2,DamageSharp));
    return dmgs;
}