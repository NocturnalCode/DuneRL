/*
 *  Heightmap.h
 *  Roguelike
 *
 *  Created by Daniel on 27/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */
 
#ifndef HEIGHTMAP_H_INC
#define HEIGHTMAP_H_INC 

#include <stdio.h>
#include <stdlib.h>

class Heightmap
{
	protected:
		double *heights;
	
	public:
		unsigned Size;
	
	Heightmap(unsigned size);
	~Heightmap();
	
	double at(unsigned i,unsigned j);
	void put(unsigned i,unsigned j,double value);
	
	Heightmap operator+( Heightmap &other );
	Heightmap operator-( Heightmap &other );
	Heightmap operator+=( Heightmap &other );
	Heightmap operator-=( Heightmap &other );
	Heightmap operator=( Heightmap &other );
    
    
    //void resize(int newSize,smoothing fucntion);
};

#endif /* HEIGHTMAP_H_INC */