//
//  Ranged.h
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef RANGED_INCLUDE_H
#define RANGED_INCLUDE_H

#include "Object.h"

class Ranged : public Object
{
public:
    Ranged();
    
    Damages getRangedDamages();
};

#endif /* RANGED_INCLUDE_H */
