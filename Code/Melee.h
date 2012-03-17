//
//  Melee.h
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef MELEE_INCLUDE_H
#define MELEE_INCLUDE_H

#include "Object.h"

class Melee : public Object
{
public:
    Melee();
    
    Damages getMeleeDamages();
};

#endif /* MELEE_INCLUDE_H */
