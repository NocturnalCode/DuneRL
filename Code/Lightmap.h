/*
 *  Lightmap.h
 *  Roguelike
 *
 *  Created by Daniel on 23/05/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef LIGHTMAP_H_INC
#define LIGHTMAP_H_INC

class Map;
class Ascii;
class LightFilter;
class Tile;
#include "Point.h"
#include "Types.h"

class Lightmap
{
protected:
    Point position;
    int radius;
    //bool* boolMap;
    int* boolMap;
    Map *map;
    
    LocalCoord world2local(WorldCoord w);
    WorldCoord local2world(LocalCoord l);
    bool isBlocked(WorldCoord co);
    bool isVisible(LocalCoord co);
    void setVisible(LocalCoord co);
    void setVisible(LocalCoord co, int debug);
    virtual bool pointInRange(Point a, Point b, int range);
    virtual void calculate();
    void cast_light(int row, float start,float end,int xx,int xy,int yx,int yy,int id);	
    void printLightMap();
    std::list<LightFilter*> lightFilters;
    
public:
    Lightmap();
    Lightmap(Point position,int radius,Map *map);
    ~Lightmap();
    virtual bool isLit(WorldCoord world);
    virtual Ascii *filter(WorldCoord world,Ascii *ascii);
    
    void addFilter(LightFilter* filter);
    void removeFilter(LightFilter* filter);
    Tile* tileAtPoint(WorldCoord point);
};

#endif /* LIGHTMAP_H_INC */


