//
//  Inventory.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Inventory.h"
#include "LabelValue.h"
#include "Stringer.h"

Inventory::Inventory(Rect rect,Player *player) : Menu(rect)
{
    this->player = player;
    
	borderStyle = Border_Single;
	getCentreLabel()->setString("Items");
	getCentreLabel()->setColour(Colour::red());
    
    groundLabel = new Label("Ground");
	groundLabel->setFrame(Rect(16,12,100,40));
    Window::add(groundLabel);
	
//	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
//	devLabel->setFrame(Rect(16,18+24,100,40));
//	devLabel->setString("Debug");
//	add(devLabel);
	
//	Label *exitLabel = new Label("Exit");
//	exitLabel->setFrame(Rect(16,18+36,100,40));
//	add(exitLabel);
}

std::string Inventory::describeObject(Object *object)
{
    std::string equipped = "";
    if(player->objectIsEquipped(object))
        equipped = stringFormat("#0f0(equipped)%");
    
    return stringFormat("%s%s",object->name.c_str(),equipped.c_str());
}

void Inventory::open()
{
    // setRect
    rect.Height = (12 * numberOfItems()) + 12 + 12 + 12;
    
    // empty all current displays
    
    // then generate new labels
    
    Objects *inv = player->getInventory();
    
    if(inv != NULL)
    {    
        int i = 0;
        foreachp(Objects, o, inv)
        {
            std::string desc = describeObject(*o);
            Label *itemLabel = new Label(desc);
            itemLabel->setFrame(Rect(18,12+(12*i),rect.Width,12));
            add(itemLabel);
            i++;
            
            printf("inv: %s",desc.c_str());
        }
    }
    
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

bool Inventory::handleEvents(SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_KEYDOWN:
			switch( event->key.keysym.sym )
        {
            case SDLK_UP:	
            {
                selectedIndex--;
                if(selectedIndex<0)
                    selectedIndex=numberOfItems()-1;
                changeSelection();
            }
                break;
            case SDLK_DOWN:
            {
                selectedIndex++;
                int max = numberOfItems()-1;
                if(selectedIndex > max)
                    selectedIndex = 0;
                changeSelection();
            }
                break;
            case SDLK_LEFT: 
            {
                LabelValue<bool,Object> *lv = dynamic_cast<LabelValue<bool,Object> *> (selected);
                if(lv != NULL)
                {
                    lv->down();
                }
            }
                break;
            case SDLK_RIGHT:
            {
                LabelValue<bool,Object> *lv = dynamic_cast<LabelValue<bool,Object> *> (selected);
                if(lv != NULL)
                {
                    lv->up();
                }
            }
                break;
            case SDLK_RETURN:
                didSelectItem(selectedIndex);
                break;
            case SDLK_i:
            case SDLK_ESCAPE:
                close();
                break;
            default:
                return false;
        }
			break;
		default:
			return false;
	}
	return true;
}