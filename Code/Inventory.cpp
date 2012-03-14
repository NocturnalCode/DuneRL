//
//  Inventory.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Inventory.h"
#include "LabelValue.h"

Inventory::Inventory(Rect rect,Player *player) : Menu(rect)
{
    this->player = player;
    
	borderStyle = Border_Single;
	getCentreLabel()->setString("Inventory");
	getCentreLabel()->setColour(Colour::red());
	
	Label *optionsLabel = new Label("Return to Game");
	optionsLabel->setFrame(Rect(16,18+12,100,40));
	add(optionsLabel);
	
//	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
//	devLabel->setFrame(Rect(16,18+24,100,40));
//	devLabel->setString("Debug");
//	add(devLabel);
	
	Label *exitLabel = new Label("Exit");
	exitLabel->setFrame(Rect(16,18+36,100,40));
	add(exitLabel);
}

void Inventory::open()
{
    // setRect
    rect.Height = 12 * numberOfItems() + 12 + 12 + 12;
    
    // empty all current displays
    
    // then generate new labels
    
    
    Menu::open();
}

void Inventory::close()
{
    Menu::close();
}

bool Inventory::wantsEvents()
{
    return true;
}

int Inventory::numberOfItems()
{
    if(player == NULL)
        return 0;
    
    Objects *inv = player->getInventory();
    if(inv == NULL)
        return 0;
    
	return inv->size();
}

void Inventory::didSelectItem(int index)
{
//	switch(index)
//	{
//		case RETURN_TO_GAME:
//			close();
//			break;
//		case DEBUG_MODE:
//			// nothing
//			break;
//		case EXIT:
//			SDL_Quit();
//			exit(0);
//			break;
//	}
}