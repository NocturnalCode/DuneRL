/*
 *  Colour.h
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#ifndef COLOUR_H_INC
#define COLOUR_H_INC 

class Colour 
{
    
public:
    float R,G,B,A;
    
    Colour();
    Colour(float r,float g,float b);
    Colour(float r,float g,float b, float a);
    Colour(unsigned int hex);
    
    void lighten();
    void lighten(float amount);
    void darken();
    void darken(float amount);
    void destaturate();
    void invert();
    
    void moreRed();
    void moreBlue();
    void moreGreen();
    
    void lessRed();
    void lessBlue();
    void lessGreen();
    
    void lerp(Colour colour, float amount);
    
    static Colour black();
    static Colour white();
    static Colour clear();
    
    static Colour red();
    static Colour green();
    static Colour blue();
    
    static Colour yellow();
    static Colour cyan();
    static Colour magenta();
    
    bool operator==(const Colour &other);
    bool operator!=(const Colour &other);
};

#endif /* COLOUR_H_INC */