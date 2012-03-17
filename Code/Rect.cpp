//
//  Rect.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Rect.h"
#include <cstdlib>

Rect::Rect() 
{
    X=0,Y=0,Width=0,Height=0;
}

Rect::Rect(int x,int y,int width,int height) 
{
    X=x,Y=y,Width=width,Height=height;
}

void Rect::inset(int x, int y)
{
    X -= x;
    Y -= y;
    Width -= x*2;
    Height -= y*2;
}

Rect randomRectInRect(Rect rect,int min, int max)
{
    int width = min+arc4random()%max;
    int height = min+arc4random()%max;
    int x = rect.X + (arc4random() % (rect.Width - width));
    int y = rect.Y + (arc4random() % (rect.Height - height)); 
    return Rect(x,y,width,height);
}