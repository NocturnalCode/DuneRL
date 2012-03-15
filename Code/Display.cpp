/*
 *  Display.cpp
 *  Roguelike
 *
 *  Created by Daniel Brooker on 4/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Display.h"
#include "Ascii.h"

Display::~Display()
{
    
}

void Display::displayTile(float *texture, float *colour, float *background, Ascii ascii)
{
	int row = ascii.Index / 16;
	int column = ascii.Index % 16;
	float ratio = 0.0625f;
	Colour fc = ascii.Foreground;
	Colour bc = ascii.Background;
    
	texture[0] = ratio*			column;		texture[1] = ratio*			row;	
	texture[2] = ratio+ratio*	column;		texture[3] = ratio*			row;
	texture[4] = ratio+ratio*	column;		texture[5] = ratio+ratio*	row;
	texture[6] = ratio*			column;		texture[7] = ratio+ratio*	row;
    
	colour[0] = fc.R;	colour[1] = fc.G; colour[2] = fc.B;  colour[3]  = fc.A;
	colour[4] = fc.R;	colour[5] = fc.G; colour[6] = fc.B;  colour[7]  = fc.A;
	colour[8] = fc.R;	colour[9] = fc.G; colour[10]= fc.B;  colour[11] = fc.A;
	colour[12] =fc.R;	colour[13] =fc.G; colour[14]= fc.B;  colour[15] = fc.A;
	
	background[0] = bc.R;	background[1] = bc.G; background[2] = bc.B;  background[3]  = bc.A;
	background[4] = bc.R;	background[5] = bc.G; background[6] = bc.B;  background[7]  = bc.A;
	background[8] = bc.R;	background[9] = bc.G; background[10]= bc.B;  background[11] = bc.A;
	background[12] =bc.R;	background[13] =bc.G; background[14]= bc.B;  background[15] = bc.A;
}