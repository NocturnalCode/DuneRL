//
//  Corpse.h
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef CORPSE_INCLUDE_H
#define CORPSE_INCLUDE_H

#include "Object.h"

class Corpse : public Object
{
public:    
    Corpse(const Monster *monster);
};

#endif /* CORPSE_INCLUDE_H */

