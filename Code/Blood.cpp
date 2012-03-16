//
//  Blood.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Blood.h"

Blood::Blood(Colour colour) : Object(new Ascii(EXCLAMATION,colour,Colour::clear()))
{
    _flags.liquid = YES;
    _flags.stackable = YES;
    _flags.decays = YES;
    
    decay = 50;
}