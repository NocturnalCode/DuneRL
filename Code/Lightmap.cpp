/*
 *  Lightmap.cpp
 *  Roguelike
 *
 *  Created by Daniel on 23/05/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Lightmap.h"
#include "Map.h"
#include "Point.h"
#include <math.h>

Lightmap::Lightmap()
{
	Lightmap(Point(0,0),1,NULL);
}

Lightmap::Lightmap(Point p,int r,Map *map)
{
    this->map = map;
	boolMap = NULL;
	position = p;
	radius = r;
	calculate();
}

bool Lightmap::isLit(WorldCoord world)
{
	LocalCoord local = world2local(world);
	if(local.X < 0 || local.Y < 0)
		return false;
	else if(local.X >= (radius*2+1) || local.Y >= (radius*2+1))
		return false;
	return isVisible(local);
}

Ascii *Lightmap::filter(WorldCoord world,Ascii *ascii)
{
    // filter the ascii 
    return ascii;
}

LocalCoord Lightmap::world2local(WorldCoord w)
{
	WorldCoord me = position;
    
    //bear in mind that the world is wrapping, the only valid answers are correct ones
    //we need to find the closest coordinate to the local space... because the world can wrap, this isn't so straightforward.
    
    //At this point only one value in the grid remains... This means we can use it to determine closest point
    switch (map->maptype) {
        case MapTypeFullTile:
        {
            int bestDist = ((me.X - w.X)*(me.X - w.X) + (me.Y - w.Y)*(me.Y - w.Y));
            WorldCoord bestPos = w;
            for (int i = 0; i<3; i++) {
                int testWX = w.X;
                if (i == 0) {
                    testWX -= map->size;
                }
                else if (i == 2) {
                    testWX += map->size;
                }
                for (int j=0; j<3; j++) {
                    int testWY = w.Y;
                    if (j==0) {
                        testWY -= map->size;
                    }
                    else if (j==2) {
                        testWY += map->size;
                    }
                    int value = ((me.X - testWX)*(me.X - testWX) + (me.Y - testWY)*(me.Y - testWY));
                    if (value < bestDist) {
                        bestPos.X = testWX;
                        bestPos.Y = testWY;
                        bestDist = value;
                    }
                }
            }
            LocalCoord local(bestPos.X-me.X+radius,bestPos.Y-me.Y+radius);
            return local;
        }
            break;
        case MapTypeWorldTile:
        {
            int bestDist = ((me.X - w.X)*(me.X - w.X) + (me.Y - w.Y)*(me.Y - w.Y));
            WorldCoord bestPos = w;
            //complex case but with only 6 tests to complete
            for (int i = 0; i < 2; i++) {
                
                for (int j = 0; j < 3; j++) {
                    int testWY = w.Y;
                    int testWX = w.X;
                    
                    //ok, but sometimes the map is flipped so we must figure this out
                    if (j==0) {
                        if (i == 0) {
                            testWX -= (map->size)/2;
                        }
                        else if (i == 1) {
                            testWX += (map->size)/2;
                        }
                        
                        
                        testWY = -testWY;//map->size;
                    }
                    else if (j==1)
                    {
                        if (i == 0) {
                            testWX -= map->size;
                        }
                        else if (i == 1) {
                            testWX += map->size;
                        }
                    }
                    else if (j==2) {
                        if (i == 0) {
                            testWX -= (map->size)/2;
                        }
                        else if (i == 1) {
                            testWX += (map->size)/2;
                        }
                        testWY = -testWY +(2*map->size);
                    }
                    int value = ((me.X - testWX)*(me.X - testWX) + (me.Y - testWY)*(me.Y - testWY));
                    if (value < bestDist) {
                        bestPos.X = testWX;
                        bestPos.Y = testWY;
                        bestDist = value;
                    }
                }
            }
            
            LocalCoord local(bestPos.X-me.X+radius,bestPos.Y-me.Y+radius);
            return local;
        }
            break;
        case MapTypeNoTile:
        default:
        {
            LocalCoord local(w.X-me.X+radius,w.Y-me.Y+radius);
            return local;
        }
            break;
    }
    
    LocalCoord local(0,0);
    return local;
}

WorldCoord Lightmap::local2world(LocalCoord l)
{
	WorldCoord me = position;
    
    unsigned size = map->size;
    int x = (me.X+l.X-radius);
    int y = (me.Y+l.Y-radius);
    switch (map->maptype) {
        case MapTypeNoTile:
            if(x<0 || y<0 || x>=size || y>=size)
            {
                x=0;
                y=0;
            }
            break;
        case MapTypeFullTile:
            x = (x) < 0 ? (size*(((-x)/size) + 1))+x : (x)%size;
            y = (y) < 0 ? (size*(((-y)/size) + 1))+y : (y)%size;
            //x = (i) < 0 ? size+i : (i)%size;
            //y = (j) < 0 ? size+j : (j)%size;
            break;
        case MapTypeWorldTile:
        {
            int realm = abs(y/size);
            bool flipped = realm %2;
            if (y<0) {
                //then flip again
                flipped = !flipped;
            }
            y = (y) < 0 ? (size*(((-y)/size) + 1))+y : (y)%size;
            if (flipped) {
                //then move x and y is upsidedownface
                x -= size/2;
                y = size - y;
            }
            x = (x) < 0 ? (size*(((-x)/size) + 1))+x : (x)%size;
        }
            break;
        default:
            x=0;
            y=0;
            break;
    } 
    if (x==size) {
        x = 0;
    }
    if (y==size) {
        y = 0;
    }
	WorldCoord world(x,y);
	return world;
}

bool Lightmap::isBlocked(WorldCoord co)
{
	return ! map->getTransparent(co.X,co.Y);
}

bool Lightmap::isVisible(LocalCoord co)
{
	int w = radius*2+1;
	return boolMap[ARRAY2D(co.X,co.Y,w)];
}

void Lightmap::setVisible(LocalCoord co)
{
	int w = radius*2+1;
	boolMap[ARRAY2D(co.X,co.Y,w)] = YES;
}
	
void Lightmap::setVisible(LocalCoord co, int debug)
{
	int w = radius*2+1;
	boolMap[ARRAY2D(co.X,co.Y,w)] = debug;
}

bool Lightmap::pointInRange(Point a, Point b, int range)
{
	if(a.X==b.X)
		return abs(a.Y-b.Y) <= range;
	else if(a.Y==b.Y)
		return abs(a.X-b.X) <= range;
	else
		return pow(a.X-b.X,2) + pow(a.Y-b.Y,2) <= range*range;
}

void Lightmap::calculate()
{
	//printf("Calculating boolMap\n\n");
	if(boolMap!=NULL)
		free(boolMap);
	//boolMap = (bool*)calloc( (radius*2+1) * (radius*2+1), sizeof(bool) );
	boolMap = (int*)calloc( (radius*2+1) * (radius*2+1), sizeof(int) );
	static int mult[4][8] = {
		{1,  0,  0, -1, -1,  0,  0,  1},
		{0,  1, -1,  0,  0, -1,  1,  0},
		{0,  1,  1,  0,  0, -1, -1,  0},
		{1,  0,  0,  1, -1,  0,  0, -1}};
	
	for(int oct = 0; oct < 8; oct++)
		cast_light(1, 1.0, 0.0, mult[0][oct], mult[1][oct], mult[2][oct], mult[3][oct], 0);
	
	//WorldCoord pos = position;
    LocalCoord local;
    local.X = radius;
    local.Y = radius;
	setVisible(local);
	
    //printLightMap();
}

void Lightmap::printLightMap()
{
    printf("\n---\n");
	for(int i = 0;i < (radius*2+1) * (radius*2+1); i++)
	{
        if (i == radius + (radius * (radius*2+1))) {
            printf("@");
        }
        else if (boolMap[i] == 0) {
            printf(" ");
        }
        else if (boolMap[i] == 1) {
            printf(".");
        }
        else if (boolMap[i] == 2) {
            printf("#");
        }
        else if (boolMap[i] == 9) {
            printf("X");
        }
        else {
            printf("%d",boolMap[i]);
        }
		
		if(i%(radius*2+1)==(radius*2))
			printf("\n");
	}
}

void Lightmap::cast_light(int row, float start,float end,int xx,int xy,int yx,int yy,int id)
{

    //printf("beginning at depth: %d", id);
	//WorldCoord posWorld = position;
    //LocalCoord pos = world2local(posWorld);
	//int cx =pos.X, cy= pos.Y;

    int cx = radius;
    int cy = radius;
	if(start < end)
		return;
	int radius_squared = radius*radius;
	
    float new_start=1.0f;
	for(int j=row; j <= radius; j++)
	{
        bool newStartSet = false;
		int dx = -j-1, dy = -j;
		bool blocked = false;
        while(dx <= 0)
		{
            
			dx++;
			int X = cx + (dx * xx) + (dy * xy);
			int Y = cy + (dx * yx) + (dy * yy);
			
			LocalCoord local = LocalCoord(X,Y);//WorldCoord(X, Y);
			WorldCoord world = local2world(local);
			

            
            if (dy < 0) {
                
            }
            
			float l_slope = ((float)dx-0.5f)/((float)dy+0.5f), r_slope= ((float)dx+0.5f)/((float)dy-0.5f);
			if(start < r_slope)
            {
				continue;
            }
			else if(end > l_slope)
				break;
			else //Our light beam is touching this square; light it
            {
                int offset = id >0 ? id + 3 : 0;
                
                if( (dx*dx + dy*dy) < radius_squared)//ensure within sight range
					setVisible(local,1+offset);
                else {
                    //printf("distance %d compared to %d\n", (dx*dx + dy*dy), radius_squared);
                    //setVisible(local,1+offset);
                    //printf("{%d,%d}\n", world.X, world.Y);
                }
                
                
                
                if (blocked)
                {
                    if(isBlocked(world))
                    {
                        
                        new_start = r_slope;
                        newStartSet = true;
                        continue;
                    }
                    else
                    {
                        blocked = false;
                        if (newStartSet) {
                            start = new_start;
                            newStartSet = false;
                        }
                        
                    }
                }
                else
                {
                    if (isBlocked(world) && (j < radius))
                    {
                        
                        blocked = true;
                        cast_light(j+1, start, l_slope, xx, xy, yx, yy, id+1);
                        new_start = r_slope;
                        newStartSet = true;
                    }
                }
            }
		}
		if(blocked)
        {
			break;
        }
	}
}
