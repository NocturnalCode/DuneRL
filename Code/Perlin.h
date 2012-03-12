/*
 *  Perlin.h
 *
 */

#include "Heightmap.h"

#ifndef PERLIN_H_INC
#define PERLIN_H_INC 

class Perlin : public Heightmap
{
	public:
		Perlin(int size, int octaves, double persistance);
        double interpolatedAt(int size, unsigned i, unsigned j);
};

#endif /* PERLIN_H_INC */