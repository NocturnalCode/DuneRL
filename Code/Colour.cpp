/*
 *  Colour.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/03/09.
 *  Copyright 2009 quantoaduro.com. All rights reserved.
 *
 */

#include "Colour.h"
#include "Random.h"
#include <cstdio>

Colour::Colour()
{
	R = 1.0;
	G = 1.0;
	B = 1.0;
	A = 1.0;
}

Colour::Colour(float r,float g,float b)
{
	R = r;
	G = g;
	B = b;
	A = 1.0;
}

Colour::Colour(float r,float g,float b,float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Colour::Colour(unsigned int hex)
{
    R = ( (hex >> 16) & 0xFF ) / 255.0f;
    G = ( (hex >> 8) & 0xFF ) / 255.0f;
	B = ( (hex) & 0xFF ) / 255.0f;
	A = 1.0f;
}

inline float Lerp(float start, float end, float amount)
{
    float difference = end - start;
    float adjusted = difference * amount;
    return start + adjusted;
}

bool Colour::operator==(const Colour &other)
{
    return R==other.R && G==other.G && B==other.B && A == other.A;
}

bool Colour::operator!=(const Colour &other)
{
    return R!=other.R || G!=other.G || B!=other.B || A != other.A;
}

void Colour::lerp(Colour colour, float amount)
{
    R = Lerp(R,colour.R,amount);
    G = Lerp(G,colour.G,amount);
    B = Lerp(B,colour.B,amount);
}

void Colour::lighten()
{
    lighten(0.1f);
}

void Colour::lighten(float amount)
{
    lerp(Colour::white(), amount);
}

void Colour::darken()
{
    darken(0.1f);
}

void Colour::darken(float amount)
{
    lerp(Colour::black(), amount);
}

void Colour::destaturate()
{
    float gray = 0.299 * R + 0.587 * G + 0.114 * B;
    R = gray;
    G = gray;
    B = gray;
}

void Colour::invert()
{
    R = 1.0f-R;
    G = 1.0f-G;
    B = 1.0f-B;
}

void Colour::moreRed()
{
    lerp(Colour::red(), 0.1);
}

void Colour::moreBlue()
{
    lerp(Colour::blue(), 0.1);
}

void Colour::moreGreen()
{
    lerp(Colour::green(), 0.1);
}

void Colour::lessRed()
{
    lerp(Colour::red(), -0.1);
}

void Colour::lessBlue()
{
    lerp(Colour::blue(), -0.1);
}

void Colour::lessGreen()
{
    lerp(Colour::green(), -0.1);
}

Colour Colour::black()
{
    return Colour(0.0f,0.0f,0.0f);
}

Colour Colour::white()
{
	return Colour(1.0f,1.0f,1.0f);
}

Colour Colour::clear()
{
	return Colour(0.0f,0.0f,0.0f,0.0f);
}

Colour Colour::red()
{
	return Colour(1.0f,0.0f,0.0f);
}
Colour Colour::green()
{
	return Colour(0.0f,1.0f,0.0f);
}
Colour Colour::blue()
{
	return Colour(0.0f,0.0f,1.0f);
}

Colour Colour::yellow()
{
	return Colour(1.0f,1.0f,0.0f);
}

Colour Colour::cyan()
{
	return Colour(0.0f,1.0f,1.0f);
}
Colour Colour::magenta()
{
	return Colour(1.0f,0.0f,1.0f);
}
