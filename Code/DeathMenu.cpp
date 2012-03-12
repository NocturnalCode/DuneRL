//
//  DeathMenu.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 12/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "DeathMenu.h"
#include "Stringer.h"

DeathMenu::DeathMenu(Rect rect,Player *player) : Menu(rect)
{
	borderStyle = Border_Double;
	getCentreLabel()->setString("Dead");
	getCentreLabel()->setColour(Colour::red());
	
	Label *optionsLabel = new Label("You have died!");
	optionsLabel->setFrame(Rect(16,18+12,100,40));
	add(optionsLabel);
	
//	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
//	devLabel->setFrame(Rect(16,18+24,100,40));
//	devLabel->setString("Debug");
//	add(devLabel);
    Label *spiceLabel = new Label(stringFormat("You collected %d spice!",player->spice));
	spiceLabel->setFrame(Rect(16,18+24,100,40));
	add(spiceLabel);
	
	Label *exitLabel = new Label("Exit");
	exitLabel->setFrame(Rect(16,18+36,100,40));
	add(exitLabel);
}

int DeathMenu::numberOfItems()
{
	return 3;
}

void DeathMenu::didSelectItem(int index)
{
	switch(index)
	{
		case 0:
			//close();
			break;
		case 1:
			// nothing
			break;
		case 2:
			SDL_Quit();
			exit(0);
			break;
	}
}