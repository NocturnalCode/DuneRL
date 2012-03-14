//
//  Point.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Point.h"
#include <cmath>
#include "Rect.h"
#include "Stringer.h"

Point::Point() 
{
    X=0,Y=0;
}

Point::Point(int x,int y) 
{
    X=x,Y=y;
}

bool Point::zero() 
{ 
    return X==0 && Y==0; 
};

bool Point::operator==(Point &other) 
{ 
    return other.X == X && other.Y == Y; 
}

bool Point::operator!=(Point &other) 
{ 
    return other.X != X || other.Y != Y; 
}

float Point::distance(Point b) 
{ 
    return sqrtf( powf(X-b.X, 2) + powf(Y-b.Y, 2)); 
}

inline Point randomPointInRect(Rect rect)
{
    return Point(rect.X + (rand() % rect.Width),rect.Y + (rand() % rect.Height));
}

inline Point centreOfRect(Rect rect)
{
    return Point(rect.X+(rect.Width/2),rect.Y+(rect.Height/2));
}

std::string Point::description()
{
    return stringFormat("{%d,%d}",X,Y);
}