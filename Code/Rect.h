//
//  Rect.h
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef RECT_H_INC
#define RECT_H_INC

class Rect
{
public:
    int X,Y,Width,Height;
    Rect();
    Rect(int x,int y,int width,int height);
    
    void inset(int x, int y);
};

Rect randomRectInRect(Rect rect,int min, int max);

#endif /* RECT_H_INC */
