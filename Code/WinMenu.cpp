//
//  WinMenu.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "WinMenu.h"
#include "Stringer.h"

WinMenu::WinMenu(Rect rect,Player *player) : Menu(rect)
{
	borderStyle = Border_Double;
	getCentreLabel()->setString("Victory");
	getCentreLabel()->setColour(Colour::red());
    
    Label *exitLabel = new Label("Exit");
	exitLabel->setFrame(Rect(16,18+36,100,40));
	add(exitLabel);
	
	Label *optionsLabel = new Label("You have won! Thanks for playing.");
	optionsLabel->setFrame(Rect(16,18+12,100,40));
	add(optionsLabel);
	
    //	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
    //	devLabel->setFrame(Rect(16,18+24,100,40));
    //	devLabel->setString("Debug");
    //	add(devLabel);
    Label *spiceLabel = new Label(stringFormat("You collected %d spice!",player->spiceCount()));
	spiceLabel->setFrame(Rect(16,18+24,100,40));
	add(spiceLabel);
}

int WinMenu::numberOfItems()
{
	return 1;
}

void WinMenu::didSelectItem(int index)
{
	switch(index)
	{
            //		case 0:
            //			//close();
            //			break;
            //		case 1:
            //			// nothing
            //			break;
		case 0:
			SDL_Quit();
			exit(0);
			break;
	}
}