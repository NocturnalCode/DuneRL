//
//  StartMenu.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "StartMenu.h"
#include "Stringer.h"

StartMenu::StartMenu(Rect rect,Player *player) : Menu(rect)
{
	borderStyle = Border_Double;
	getCentreLabel()->setString("Planet Arrakis 'Dune'");
	getCentreLabel()->setColour(Colour::red());
    
    Label *exitLabel = new Label("[Enter]");
	exitLabel->setFrame(Rect(256-48+12,18+36+24,100,40));
	add(exitLabel);
	
	Label *optionsLabel = new Label("You've been separated from your spice collecting party.");
	optionsLabel->setFrame(Rect(16,18+12,100,40));
	add(optionsLabel);
	
    Label *spiceLabel = new Label("Make your way back to your base in the southern hemisphere.");
	spiceLabel->setFrame(Rect(16,18+24,100,40));
	add(spiceLabel);
	
    Label *label = new Label("Find water, utilise the spice, survive the storm.");
	label->setFrame(Rect(16,18+36,100,40));
	add(label);
}

int StartMenu::numberOfItems()
{
	return 1;
}

void StartMenu::didSelectItem(int index)
{
	switch(index)
	{
		case 0:
			close();
			break;
		case 1:
			// nothing
			break;
		case 2:
//			SDL_Quit();
//			exit(0);
			break;
	}
}

bool StartMenu::handleEvents(SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_KEYDOWN: // the any key
            close();
            break;
		default:
			return false;
	}
	return true;
}