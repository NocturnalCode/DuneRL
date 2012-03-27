/*
 *  Random.cpp
 *  Roguelike
 *
 *  Created by Daniel on 2/05/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "Random.h"

Random::Random(unsigned long seed)
{
    this->seed = seed;
    int_r = new MTRand(seed);
    double_r = new MTRand_open(seed);
}

int Random::getInt()
{
    return (*int_r)();
}

float Random::getFloat()
{
    return static_cast<float>((*double_r)());
}

double Random::getDouble()
{
    return (*double_r)();
}

#ifdef _WIN32
#include <time.h>
int arc4random()
{
	static bool once = false;
	if(!once)
	{
		srand((unsigned)time(NULL));
		once = true;
	}
	return rand();
}

#endif