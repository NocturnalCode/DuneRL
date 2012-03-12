/*
 *  Label.cpp
 *  Roguelike
 *
 *  Created by Daniel on 2/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Label.h"
#include "Roguelike.h"

Label::Label()
{
	Label("");
}

Label::Label(std::string text)
{
	parent = NULL;
	this->text = text;
	colour = Colour::white();
	bgColour = Colour::black();
	selected = false;
}

void Label::setString(std::string text)
{
	this->text = text;
}

std::string Label::getString()
{
	return text;
}

void Label::setColour(Colour colour)
{
	this->colour = colour;
}

Colour Label::getColour()
{
	return colour;
}

void Label::setBackgroundColour(Colour colour)
{
	this->bgColour = colour;
}

Colour Label::getBackgroundColour()
{
	return bgColour;
}

void Label::setFrame(Rect frame)
{
	this->frame = frame;
}

Rect Label::getFrame()
{
	return frame;
}

void Label::setParent(Display* parent)
{
	this->parent = parent;
}

Display* Label::getParent()
{
	return parent;
}

void Label::setSelected(bool sel)
{
	selected = sel;
}

bool Label::getSelected()
{
	return selected;
}

void Label::setMultiline(bool enable,int left, int right)
{
}

void Label::setAlignment(LabelAlign align)
{
}

float floatFromHex(char hexChar)
{
    float value = 1.0f;
    switch(hexChar)
    {
        case '0': value=0.0f; break;
        case '1': value=1.0f; break;
        case '2': value=2.0f; break;
        case '3': value=3.0f; break;
        case '4': value=4.0f; break;
        case '5': value=5.0f; break;
        case '6': value=6.0f; break;
        case '7': value=7.0f; break;
        case '8': value=8.0f; break;
        case '9': value=9.0f; break;
        case 'a':
        case 'A': value=10.0f; break;
        case 'b':
        case 'B': value=11.0f; break;
        case 'c':
        case 'C': value=12.0f; break;
        case 'd':
        case 'D': value=13.0f; break;
        case 'e':
        case 'E': value=14.0f; break;
        case 'f':
        case 'F': value=15.0f; break;
    }
    return value/15.0f;
}

Colour colourFromString(std::string hex)
{
    return Colour(floatFromHex(hex[0]), floatFromHex(hex[1]), floatFromHex(hex[2]));
}

void Label::display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates)
{
	unsigned tileW = (4*2);
	unsigned tileH = (6*2);
	unsigned width = parent->getFrame().Width;//, height = parent->getFrame().Height;
	unsigned nWide = width/tileW;
	//unsigned nHigh = height/tileH;
	unsigned xOff = frame.X/tileW;
	unsigned yOff = frame.Y/tileH;
	
	int i=0;
    std::string print = prefix() + text + suffix();
    
    Colour c1,c2;
    if(!selected)
    {
        c1 = colour;
        c2 = bgColour;
    }
    else
    {
        c1 = bgColour;
        c2 = colour;
    }
    
    int debug = 0;
	for(int m=0;m < print.size();m++)
	{        
        if(print[m]=='#') //eg #f0f
        {
            m += 4;
            if(!selected)
                c1 = colourFromString(print.substr(m-3,m-1));
        }
        else if(print[m]=='%')
        {
            if(!selected)
            {
                c1 = colour;
                c2 = bgColour;
            }
            else
            {
                c1 = bgColour;
                c2 = colour;
            }
            
            m++;
        }
        else if(print[m]=='<')
        {
            debug++;
            continue;
        }
        else if(print[m]=='>')
        {
            debug--;
            continue;
        }
        
        if(debug > 0 && !DEV)
        {
            continue;
        }
        
		int texI = ARRAY2D((i+xOff),yOff,nWide)*8;
		int colI = ARRAY2D((i+xOff),yOff,nWide)*16;
        
		Ascii a = Ascii(CHAR_TO_ASCII(print[m])+16,c1,c2); 
		displayTile(&texCoordinates[texI],&colCoordinates[colI],&bgColCoordinates[colI],a);
        i++;
    }
}