/*
 *  Ascii.cpp
 *  Roguelike
 *
 *  Created by Daniel Brooker on 6/04/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#include "Ascii.h"
#include "Colour.h"

Ascii::Ascii()
{
    backgroundInherits = false;
    Index = rand()%256;
    Foreground = Colour( (float)(rand()%255)/255.0, (float)(rand()%255)/255.0, (float)(rand()%255)/255.0 );
    Background = Colour( (float)(rand()%255)/255.0, (float)(rand()%255)/255.0, (float)(rand()%255)/255.0 );
}

Ascii::Ascii(SpriteIndex index, float red,float green, float blue)
{
    backgroundInherits = false;
    Index = index;
    Foreground = Colour( red, green, blue);
    Background = Colour::black();
    
}

Ascii::Ascii(SpriteIndex index, Colour fg,Colour bg)
{
    backgroundInherits = false;
    Index = index;
    Foreground = fg;
    Background = bg;
    if (bg == Colour::clear()) {
        backgroundInherits = true;
    }
}

Ascii& Ascii::operator=(const Ascii& a) 
{
    if (this != &a) 
    { 
		Index = a.Index;
		Foreground = a.Foreground;
		Background = a.Background;
    }
    return *this; 
}

/// ASCII GROUP

AsciiGroup::AsciiGroup()
{
}

AsciiGroup::AsciiGroup(Ascii *ascii) 
{ 
	asciis.push_back(ascii); 
	index = 0; 
}

AsciiGroup::AsciiGroup(Asciis asciis) 
{ 
	this->asciis = asciis; 
	index = 0; 
}

Ascii* AsciiGroup::currentAscii() 
{ 
	return asciis[index]; 
};

void AsciiGroup::update() 
{ 
	index = (index+1)%asciis.size(); 
}

RandomAscii::RandomAscii(Asciis asciis) 
{ 
	this->asciis = asciis; 
	index = 0; 
}

void RandomAscii::update() 
{ 
	index = rand()%asciis.size(); 
}
