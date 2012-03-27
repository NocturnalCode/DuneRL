/*
 *  Random.h
 *  Roguelike
 *
 *  Created by Daniel on 2/05/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#ifndef RANDOM_H_INC
#define RANDOM_H_INC

#include <cstdlib>
#include "mtrand.h"

class Random 
{	
    
private:
    unsigned long seed;
    MTRand *int_r;
    MTRand_open *double_r;
    
public:
    
    Random(unsigned long seed);
    
    int getInt();
    float getFloat();
    double getDouble();
};

#ifdef _WIN32
int arc4random();
#endif

#endif /* RANDOM_H_INC */