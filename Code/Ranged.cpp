//
//  Ranged.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Ranged.h"
#include "Ascii.h"

Ranged::Ranged() : Object(new Ascii(BRACKET_RIGHT_CURLY,Colour::white(), Colour::clear()))
{
    _flags.wieldable = YES;
    name = "ranged weapon";
}

Damages Ranged::getRangedDamages()
{
    Damages dmgs;
    dmgs.push_back(Damage(3,DamagePierce));
    return dmgs;
}