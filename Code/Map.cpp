/*
 *  Map.cpp
 *  Roguelike
 *
 *  Created by Daniel on 4/04/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#include "Map.h"
#include "World.h"

#include "Monster.h"
#include "Roguelike.h"
#include "Rect.h"


Map::Map(unsigned Size)
{
	size = Size;
	tex = NULL;
	col = NULL;
	tiles = new std::vector<std::vector<Tile*>*>(); //(Tile**)calloc(size*size,sizeof(Tile*));
//    for (int i = 0; i<Size; i++) {
//        tiles->push_back(new std::vector<Tile*>());
//    }
    heights = NULL;
	maptype = MapTypeWorldTile;
    mapFlipped = false;
    mapFlippednessChanged = false;

    visibleRect = Rect(0-40+1,0-20+1,80,40);
    mapRect = Rect(0,0,0,0);
	//generate();
}

Map::~Map()
{
    for(int i=0;i< size;i++)
	{
		for(int j=0;j<size;j++)
		{
            VVARRAYPP(i, j, tiles)->parent = NULL;
            delete VVARRAYPP(i, j, tiles);
		}
        VARRAYP(i, tiles)->clear();
	}
    tiles->clear();
    delete tiles;
}

void Map::generate()
{
	//int i,j;
	
	//Perlin heights(size, 3,1.0);
	heights = new Perlin(size, 3, 1.0);
//	for(j=0;j<size;j++)
//    {
//		for(i=0;i< size;i++) 
//        {
//            VARRAYP(i, tiles)->push_back(this->generateTileAtCoord(i, j));
//        }
//    }
    
    this->setVisibleRect(visibleRect);
    
    return;
	
	/*
		Generation Stages
		- - - - - - - - -
		Rock
		Ground
		Plants
		Cities
		Items
		Creeps
		Treasure
		- - - - - - - - -
	*/
	
//	createRoom(Rect(10,10,10,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(30, 5,10,20),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(50,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));
//	createRoom(Rect(70,20,20,10),Ascii(4,Colour(1.0f,1.0f,1.0f),Colour(0.0f,0.3f,0.2f)));

	printf("Generated map of size %dx%d\n",size,size);
}

Tile* Map::generateTileAtCoord(int i, int j)
{
    Tile *t = new Tile(i, j);
    t->parent = this;
    
    double h = heights->at(i,j) + 1;
    std::vector<int> ascii;
    ascii.push_back(COMMA);
    ascii.push_back(QUOTE_SINGLE);
    ascii.push_back(0);
    
    Colour foreground(0.1f,(float)((int)(i*h)%4)*0.2,0.f);
    Colour background(Colour(0,h/5.0,0));
    
    Object *o = new Object(new Ascii(ascii[rand()%ascii.size()],foreground,background));
    
    t->Position = Point(i,j);
    o->setPassable(true);
    t->addObject(o);
    
    return t;
}

void Map::createRoom(Rect rect,Ascii floor)
{
	Object* o;
	for(int i=rect.X;i<rect.X+rect.Width-1;i++)
	{
		for(int j=rect.Y;j<rect.Y+rect.Height-1;j++)
		{
			o = new Object(new Ascii(floor));
			o->setPassable(true);
			addObject(i,j,o);
		}
	}
	
	//top left
	o = new Object(new Ascii(CORNER_TOP_LEFT_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X,rect.Y,o);
	//top right
	o = new Object(new Ascii(CORNER_TOP_RIGHT_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X+rect.Width-1,rect.Y,o);
		
	//bottom left
	o = new Object(new Ascii(CORNER_BOTTOM_LEFT_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X,rect.Y+rect.Height-1,o);
	//bottom right
	o = new Object(new Ascii(CORNER_BOTTOM_RIGHT_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
	o->setPassable(false);
	o->setTransparent(false);
	addObject(rect.X+rect.Width-1,rect.Y+rect.Height-1,o);
	
	for(int j=rect.Y+1;j<rect.Y+rect.Height-1;j++)
	{
		o = new Object(new Ascii(LINE_VERTICAL_DOUBLE +16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
		o->setPassable(false);
		o->setTransparent(false);
		addObject(rect.X,j,o);
		addObject(rect.X+rect.Width-1,j,o);
	}
	
	for(int i=rect.X+1;i<rect.X+rect.Width-1;i++)
	{
		if(i==(int)(rect.X+(rect.Width/2)))
		{
			o = new Object(new Ascii(JOINT_DOUBLE_CENTER_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(1.0,0.5,0))); // a door
		}
		else
		{
			o = new Object(new Ascii(LINE_HORIZONTAL_DOUBLE+16,Colour(1.0f,1.0f,1.0f),Colour(0.2f,0.3f,0.2f)));
			o->setPassable(false);
		}
		o->setTransparent(false);
		addObject(i,rect.Y,o);
		addObject(i,rect.Y+rect.Height-1,o);
	}
	
	printf("Creating room: %d %d %d %d\n",rect.X,rect.Y,rect.Width,rect.Height);
}

bool rectContains(Point origin, int width, int height, Point test)
{
    if (test.X >= origin.X && test.X < origin.X + width) {
        if (test.Y >= origin.Y && test.Y < origin.Y + height) {
            return true;
        }
    }
    return false;
}

Tile *Map::getTile(WorldCoord point)
{
    WorldCoord p = this->convertWorldCoordRelativeToMapCoord(point);
    if (p.X < 0 || p.Y < 0) {
        return NULL;
    }
    
    Point v1 = this->convertWorldCoordRelativeToMapCoord(Point(mapRect.X, mapRect.Y));
    if (rectContains(v1, mapRect.Width, mapRect.Height, p)) {
        //then we are in the coord space of v1
        return VVARRAYPP(p.X-v1.X, p.Y-v1.Y, tiles);
    }
    Point v2 = this->convertWorldCoordRelativeToMapCoord(Point(mapRect.X+mapRect.Width, mapRect.Y));
    v2.X -= mapRect.Width;
    if (rectContains(v2, mapRect.Width, mapRect.Height, p)) {
        //then we are in the coord space of v2
        return VVARRAYPP(p.X-v2.X, p.Y-v2.Y, tiles);
    }
    Point v3 = this->convertWorldCoordRelativeToMapCoord(Point(mapRect.X, mapRect.Y+mapRect.Height));
    v3.Y -= mapRect.Height;
    if (rectContains(v3, mapRect.Width, mapRect.Height, p)) {
        //then we are in the coord space of v2
        return VVARRAYPP(p.X-v3.X, p.Y-v3.Y, tiles);
    }
    Point v4 = this->convertWorldCoordRelativeToMapCoord(Point(mapRect.X+mapRect.Width, mapRect.Y+mapRect.Height));
    v4.X -= mapRect.Width;
    v4.Y -= mapRect.Height;
    if (rectContains(v4, mapRect.Width, mapRect.Height, p)) {
        //then we are in the coord space of v2
        return VVARRAYPP(p.X-v4.X, p.Y-v4.Y, tiles);
    }
    //Point cp2 = this->convertWorldCoordRelativeToMapCoord(cp);
	return NULL;//VVARRAYPP(p.X-cp.X, p.Y-cp.Y, tiles);//tiles[ARRAY2D(x,y,size)];
}

WorldCoord Map::convertWorldCoordRelativeToMapCoord(WorldCoord point)
{
    int x = (point.X);
	int y = (point.Y);
    
    switch (maptype) {
        case MapTypeNoTile:
            if(x<0 || y<0 || x>=size || y>=size)
                return Point(-1, -1);
            break;
        case MapTypeFullTile:
            x = (x) < 0 ? (size*(((-x)/size) + 1))+x : (x)%size;
            y = (y) < 0 ? (size*(((-y)/size) + 1))+y : (y)%size;
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
                y = size - y-1;
            }
            x = (x) < 0 ? (size*(((-x)/size) + 1))+x : (x)%size;
        }
            break;
        default:
            return Point(-1, -1);
            break;
    } 
    if (x==size) {
        x = 0;
    }
    if (y==size) {
        y = 0;
    }
    return Point(x,y);
}

void Map::addObject(int i, int j,Object *object)
{
    Tile* tile = this->getTile(Point(i,j));
    if (tile == NULL) {
        return;
    }
	tile->addObject(object);
}

void Map::removeObject(Object *object)
{
	object->removeFromTile();
}

void Map::moveObject(Object *object, int i, int j)
{    
    Tile* tile = this->getTile(Point(i,j));
    if (tile == NULL) {
        return;
    }
	object->removeFromTile();
	tile->addObject(object);
}


bool Map::adjustPlayer(int i, int j)
{
	Point p = player->getParent()->Position;
	int x = p.X + i;//((p.X+i) < 0 ? size+(p.X+i) : (p.X+i)%size);
    

	int y = mapFlipped ? p.Y - j : p.Y + j;//((p.Y+j) < 0 ? size+(p.Y+j) : (p.Y+j)%size);
    if (y < 0 || y >= size) {
        mapFlipped = !mapFlipped;
    }
//    else {
//        mapFlippednessChanged = false;
//    }
    switch (maptype) {
        case MapTypeNoTile:
            if(x<0 || y<0 || x>=size || y>=size)
                return false;
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
                //y = p.Y - j;
                flipped = !flipped;
            }
            y = y < 0 ? (size*(((-y)/size) + 1))+y : (y)%size;
            if (flipped) {
                //then move x and y is upsidedownface
                x -= size/2;
                y = size - y-1;
                
            }
//            if (mapFlippednessChanged) {
//                mapFlipped = flipped;
//            }
            
            x = (x) < 0 ? (size*(((-x)/size) + 1))+x : (x)%size;
        }
            break;
        default:
            return false;
            break;
    } 
    if (x==size) {
        x = 0;
    }
    if (y==size) {
        y = 0;
    }
	if(checkMove(player,x,y))
	{
		moveObject(player,x,y);
        this->setVisibleRect(Rect(x-40+1,y-20+1,80,40));
		return true;
	}
    else if(checkCombat(player,x,y)) // this is less check combat and more do melee combat, refactor
    {
        
    }
    else if(checkAction(player,x,y))
    {
        
    }
	return false;
}



void Map::setVisibleRect(Rect visiRect)
{
    //Do the tile generate thing and make sure there are tiles for what is visible
    
    //ok, we want to make the map rect basically the same as the visiRect except with padding
    
    Rect newMapRect = visiRect;
    int padding = 20;
    newMapRect.X -= padding;
    newMapRect.Y -= padding;
    newMapRect.Width += 2*padding;
    newMapRect.Height += 2*padding;
    
    //we need to shift the current arrays by the difference... no simple task as there are 2 axes to do this on
    
    int xDiff = newMapRect.X - mapRect.X;
    int yDiff = newMapRect.Y - mapRect.Y;
    printf("tiles size = %d", tiles->size());
    if (tiles->size() == 0) {
        for(int i=0;i< newMapRect.Width;i++)
        {
            tiles->push_back(new std::vector<Tile*>());
            for(int j=0;j<newMapRect.Height;j++)
            {
                VARRAYP(i, tiles)->push_back(this->generateTileAtCoord(i+newMapRect.X, j+newMapRect.Y));
            }
        }
        xDiff = 0;
        yDiff = 0;
    }
    
    
    mapRect = newMapRect;
    if (xDiff > 0) {
        //then shift main Array to the left by diff
        
        //typically diff will be 1 but, in the case that it isn't we need to be able to handle that
        //if (xDiff > mapRect.Width) {
            //Then the mapRect has been moved so far as to make the current world obsolete.
        //int end = mapRect.Width - 1;
        int totalToRemove = MIN(xDiff, mapRect.Width);
        for(int i=0;i < totalToRemove;i++)
        {
            for(int j=0;j<mapRect.Height;j++)
            {
                VVARRAYPP(i, j, tiles)->parent = NULL;
                delete VVARRAYPP(i, j, tiles);
            }
            delete VARRAYP(i, tiles);
        }
        tiles->erase(tiles->begin(), tiles->begin()+totalToRemove);
        //now add on the same to the end
        for(int i=mapRect.Width-totalToRemove;i<mapRect.Width;i++)
        {
            tiles->push_back(new std::vector<Tile*>());
            for(int j=0;j< mapRect.Height;j++) 
            {
                WorldCoord coord = this->convertWorldCoordRelativeToMapCoord(Point(newMapRect.X + i, newMapRect.Y+j));
                VARRAYP(i, tiles)->push_back(this->generateTileAtCoord(coord.X, coord.Y));
            }
        }
    }
    else if (xDiff < 0)
    {
        //then shift the main Array to the right by diff
        xDiff = -xDiff;
        //int end = mapRect.Width - 1;
        int totalToRemove = MIN(xDiff, mapRect.Width);
        for(int i= mapRect.Width-totalToRemove;i < mapRect.Width;i++)
        {
            for(int j=0;j<mapRect.Height;j++)
            {
                VVARRAYPP(i, j, tiles)->parent = NULL;
                delete VVARRAYPP(i, j, tiles);
            }
            delete VARRAYP(i, tiles);
        }
        tiles->erase(tiles->end()-totalToRemove, tiles->end());
        //now add on the same to the end
        for(int i=0;i<totalToRemove;i++)
        {
            tiles->insert(tiles->begin()+i, new std::vector<Tile*>());
            //tiles->push_back();
            for(int j=0;j< mapRect.Height;j++) 
            {
                WorldCoord coord = this->convertWorldCoordRelativeToMapCoord(Point(newMapRect.X + i, newMapRect.Y+j));
                VARRAYP(i, tiles)->push_back(this->generateTileAtCoord(coord.X, coord.Y));
            }
        }
    }
    if (yDiff > 0) {
        //then shift sub Arrays to the left by diff
        
        
        int totalToRemove = MIN(yDiff, mapRect.Height);
        for(int i=0;i < mapRect.Width;i++)
        {
            std::vector<Tile*> *sub = VARRAYP(i, tiles);
            for(int j=0;j<totalToRemove;j++)
            {
                VVARRAYPP(i, j, tiles)->parent = NULL;
                delete VVARRAYPP(i, j, tiles);
            }
            sub->erase(sub->begin(), sub->begin()+totalToRemove);
        }
        //now add on the same to the end
        for(int i=0;i<mapRect.Width;i++)
        {
            for(int j=mapRect.Height-totalToRemove;j< mapRect.Height;j++) 
            {
                WorldCoord coord = this->convertWorldCoordRelativeToMapCoord(Point(newMapRect.X + i, newMapRect.Y+j));
                VARRAYP(i, tiles)->push_back(this->generateTileAtCoord(coord.X, coord.Y));
            }
        }
        
    }
    else if (yDiff < 0)
    {
        //then shift sub Arrays to the right by diff
        yDiff = -yDiff;
        int totalToRemove = MIN(yDiff, mapRect.Height);
        for(int i=0;i < mapRect.Width;i++)
        {
            std::vector<Tile*> *sub = VARRAYP(i, tiles);
            for(int j=mapRect.Height - totalToRemove;j<mapRect.Height;j++)
            {
                VVARRAYPP(i, j, tiles)->parent = NULL;
                delete VVARRAYPP(i, j, tiles);
            }
            sub->erase(sub->end(), sub->end()-totalToRemove);
        }
        //now add on the same to the end
        for(int i=0;i<mapRect.Width;i++)
        {
            for(int j=0;j< totalToRemove;j++) 
            {
                WorldCoord coord = this->convertWorldCoordRelativeToMapCoord(Point(newMapRect.X + i, newMapRect.Y+j));
                VARRAYP(i, tiles)->insert(VARRAYP(i, tiles)->begin()+j, this->generateTileAtCoord(coord.X, coord.Y));
            }
        }
    }
    
    visibleRect = visiRect;
}

Rect Map::getVisibleRect()
{
    return visibleRect;
}

void Map::setPlayer(Monster *player)
{
	this->player = player;
	// Player
    Point p = player->getPosition();
	this->setVisibleRect(Rect(p.X-40+1,p.Y-20+1,80,40));
	player->calculateSight();
}

Monster *Map::getPlayer()
{
	return this->player;
}

void World::setParent(Display* parent)
{
	this->parent = parent;
}


bool Map::checkMove(Object *object, int i, int j)
{
    Tile* tile = this->getTile(Point(i,j));
    if (tile == NULL) {
        return false;
    }
    bool passable = tile->_flags.passable==YES;
    
	return passable;
}

bool Map::checkCombat(Monster *monster, int i, int j)
{    
    Tile* tile = this->getTile(Point(i,j));
    if (tile == NULL) {
        return false;
    }
    bool passable = tile->_flags.passable==YES;
    
    if(!passable)
    {
        Object *object = tile->getTopObject();
        Monster *target = dynamic_cast<Monster *>(object);
        if(target != NULL)
        {
            Damages damages = target->calculateMeleeDamagesFrom(monster);
            foreach(Damages, dmg, damages)
            {
                Damage damage = (*dmg);
                LOG("Hit %s.< #AA0%d dmg>",target->name.c_str(),damage.damage);
                target->adjustHP(-damage.damage);
                //LOG("<%s.>",target->hpDescription().c_str());
                
                target->onDamagedBy(monster, damage);
                monster->onDamagedObject(target,damage);
            }
            
            return true;
        }
    }
	return false;
}

bool Map::checkAction(Object *object, int i, int j)
{
    Tile* tile = this->getTile(Point(i,j));
    if (tile == NULL) {
        return false;
    }
    bool passable = tile->_flags.passable==YES;
    
    if(!passable)
    {
//        Object *object = tile.getTopObject();
        //LOG("Tile %d,%d passable=%d %s",i,j,passable,object->name.c_str());
        return true;
    }
	return false;
}

#define plot(x,y) end=Point(x,y); LOG("<[LOS] %d,%d>",x,y)

/// Bresenham
/// http://roguebasin.roguelikedevelopment.org/index.php/Bresenham%27s_Line_Algorithm
// Could probably extract this into a Bresham class for other line purposes
bool Map::lineOfSight(Point a,Point b)
{
    int x1 = a.X;
    int y1 = a.Y;
    int x2 = b.X;
    int y2 = b.Y;
    
    Point end;
    
    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x(x2 - x1);
    signed char ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
    
    int delta_y(y2 - y1);
    signed char iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    
    plot(x1, y1);
    
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        
        while (x1 != x2)
        {
            if (error >= 0)
            {
                if (error || (ix > 0))
                {
                    y1 += iy;
                    error -= delta_x;
                }
                // else do nothing
            }
            // else do nothing
            
            x1 += ix;
            error += delta_y;
            
            plot(x1, y1);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        
        while (y1 != y2)
        {
            if (error >= 0)
            {
                if (error || (iy > 0))
                {
                    x1 += ix;
                    error -= delta_y;
                }
                // else do nothing
            }
            // else do nothing
            
            y1 += iy;
            error += delta_x;
            
            plot(x1,y1);
        }
    }
    
    return end == b;
}

Objects Map::getVisibleMonsters(Object *origin,int range)
{
    Objects visible;
    Point p1 = origin->getPosition();
    
    int range_squared = range * range;
    
    foreach(Monsters, m, monsters)
    {
        if((*m)!=origin)
        {
            Point p2 = (*m)->getPosition();
            int dx = p1.X-p2.X;
            int dy = p1.Y-p2.Y;
            if((dx*dx)+(dy*dy) < range_squared)
            {
                if(lineOfSight(p1, p2))
                {
                    visible.push_back((*m));
                }
            }
        }
    }
    
    return visible;
}

Objects Map::getVisibleObjects(Object *origin,int range)
{
    Objects visible;
    Point p1 = origin->getPosition();
    
    int range_squared = range * range;
    
    foreach(Objects, o, objects)
    {
        if((*o)!=origin)
        {
            Point p2 = (*o)->getPosition();
            int dx = p1.X-p2.X;
            int dy = p1.Y-p2.Y;
            if((dx*dx)+(dy*dy) < range_squared)
            {
                if(lineOfSight(p1, p2))
                {
                    visible.push_back((*o));
                }
            }
        }
    }
    
    return visible;
}

void Map::update(Speed turnSpeed)
{
    //We want to go through the visible tiles and get each one to compute what it should do. If a tile has a monster on it, then the monster should move too.
    
    if (player->isAlive() == false) {
        return;
    }
    
    
    Rect updateRect = this->getVisibleRect();// visibleRect;
    int padding = 20;
    updateRect.X -= padding;
    updateRect.Y -= padding;
    updateRect.Width += padding*2;
    updateRect.Height += padding*2;
    
    
    int i=updateRect.X,j=updateRect.Y; // world
	int x=0,y=0; // local
	player->update(turnSpeed, world->getTurn());
	for(j=updateRect.Y,y=0;y< updateRect.Height;j++,y++)
	{
		for(i=updateRect.X,x=0;x< updateRect.Width;i++,x++)
		{
            if (player->isAlive() == false) {
                return;
            }
            WorldCoord point;
            point.X = i;
            point.Y = j;
            Tile* tile = getTile(point);
            if (tile == NULL) {
                continue;
            }
            tile->update(turnSpeed,world->getTurn());
            
            
        }
    }
}

//-- Display stuff
void Map::updateAscii()
{
    /// change this to be onscreen only updates
    
    //	Environment stuff
//	foreach(Objects,o,objects)	
//        (*o)->updateAscii();
//    
//	foreach(Monsters,m,monsters)	
//        (*m)->updateAscii();
}

void Map::setTexturePointer(float *texturePointer)
{
	tex = texturePointer;
}

void Map::setColourPointer(float *colourPointer)
{
	col = colourPointer;
}

void Map::setBackgroundColourPointer(float *colourPointer)
{
	bgCol = colourPointer;
}

bool Map::getTransparent(int x, int y)
{
	return VVARRAYPP(x, y, tiles)->_flags.transparent;
}

void Map::display()
{
    Rect rect = this->getVisibleRect();//visibleRect;
	
//    printf("VisibleRect {{%d,%d},{%d,%d}} size=%d\n",rect.X,rect.Y,rect.Width,rect.Height,size);

	int i=rect.X,j=rect.Y; // world
	int x=0,y=0; // local
	
	for(j=rect.Y,y=0;y< rect.Height;j++,y++)
	{
		for(i=rect.X,x=0;x< rect.Width;i++,x++)
		{
            //printf("x=%d y=%d\n",i,j);
            int argY = mapFlipped?rect.Height-y-1:y;
            
			int texI = ARRAY2D(x,argY,rect.Width)*8;
			int colI = ARRAY2D(x,argY,rect.Width)*16;
        
            int dx = (i)-mapRect.X;// < 0 ? size+i : (i)%size;
            
            
            int dy =(j)-mapRect.Y;// < 0 ? size+j : (j)%size;
//            if (mapFlipped && rect.Height%2 == 0) {
//                dy -= 1;
//            }
//            
//            switch (maptype) {
//                case MapTypeNoTile:
//                    if(dx<0 || dy<0 || dx>=size || dy>=size)
//                    {
//                        displayTile(&tex[texI],&col[colI],&bgCol[colI],NULL,NULL);
//                        continue;
//                    }
//                    break;
//                case MapTypeFullTile:
//                    dx = (dx) < 0 ? (size*(((-dx)/size) + 1))+dx : (dx)%size;
//                    dy = (dy) < 0 ? (size*(((-dy)/size) + 1))+dy : (dy)%size;
//                    //x = (i) < 0 ? size+i : (i)%size;
//                    //y = (j) < 0 ? size+j : (j)%size;
//                    break;
//                case MapTypeWorldTile:
//                {
//                    int realm = abs(dy/size);
//                    bool flipped = realm %2;
//                    if (dy<0) {
//                        //then flip again
//                        flipped = !flipped;
//                    }
//                    dy = (dy) < 0 ? (size*(((-dy)/size) + 1))+dy : (dy)%size;
//                    if (flipped) {
//                        //then move x and y is upsidedownface
//                        dx -= size/2;
//                        dy = size - dy-1;
//                    }
//                    dx = (dx) < 0 ? (size*(((-dx)/size) + 1))+dx : (dx)%size;
//                }
//                    break;
//                default:
//                    displayTile(&tex[texI],&col[colI],&bgCol[colI],NULL,NULL);
//                    continue;
//                    break;
//            }
//            if (dx==size) {
//                dx = 0;
//            }
//            if (dy==size) {
//                dy = 0;
//            }
			//int pos = ARRAY2D(dx,dy,size);
			Tile* tile = VVARRAYPP(dx, dy, tiles);
			displayTile(&tex[texI],&col[colI],&bgCol[colI],tile,player);
		}
	}
                   
}

void Map::displayTile(float *texture, float *colour,float *backgroundColour, Tile *tile, Monster *monster)
{
    
	Point p = tile != NULL ? tile->Position : Point(0, 0);
	Ascii *ascii;
	int row, column;
	float ratio = 0.0625f;
	Colour fc,bc;
	
	bool visible = monster != NULL ? monster->canSee(p.X,p.Y) : false;
	ascii = tile != NULL ? tile->getTopAscii(visible||DEV) : NULL;
	
    Lightmap *lm = monster->getSightMap();
    if(lm)
    {
        if (ascii != NULL) {
            //const Ascii a = *ascii;
            ascii = new Ascii(*ascii);
            ascii = lm->filter(p, ascii);
        }
        
    }
    
	float m = ( visible ? 1 : 0.2 ); 
	
	if(DEV&&!visible)
		m = 0.5;
	
	if(ascii != NULL)
	{
		row = ascii->Index / 16;
		column = ascii->Index % 16;
		fc = ascii->Foreground;
		bc = ascii->Background;
	}
	else
	{
		row = 0;
		column = 0;
		fc = Colour::black();
		bc = Colour::black();
	}
    
    if (lm) {
        if (ascii != NULL) {
            delete ascii;
        }
        
    }
    
	texture[0] = ratio*			column;		texture[1] = ratio*			row;	
	texture[2] = ratio+ratio*	column;		texture[3] = ratio*			row;
	texture[4] = ratio+ratio*	column;		texture[5] = ratio+ratio*	row;
	texture[6] = ratio*			column;		texture[7] = ratio+ratio*	row;

	colour[0] = fc.R*m;	colour[1] = fc.G*m; colour[2] = fc.B*m;  colour[3]  = fc.A;
	colour[4] = fc.R*m;	colour[5] = fc.G*m; colour[6] = fc.B*m;  colour[7]  = fc.A;
	colour[8] = fc.R*m;	colour[9] = fc.G*m; colour[10]= fc.B*m;  colour[11] = fc.A;
	colour[12] =fc.R*m;	colour[13] =fc.G*m; colour[14]= fc.B*m;  colour[15] = fc.A;
	
	backgroundColour[0] = bc.R*m;	backgroundColour[1] = bc.G*m; backgroundColour[2] = bc.B*m;  backgroundColour[3]  = bc.A;
	backgroundColour[4] = bc.R*m;	backgroundColour[5] = bc.G*m; backgroundColour[6] = bc.B*m;  backgroundColour[7]  = bc.A;
	backgroundColour[8] = bc.R*m;	backgroundColour[9] = bc.G*m; backgroundColour[10]= bc.B*m;  backgroundColour[11] = bc.A;
	backgroundColour[12] =bc.R*m;	backgroundColour[13] =bc.G*m; backgroundColour[14]= bc.B*m;  backgroundColour[15] = bc.A;
}
