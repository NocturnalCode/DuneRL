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
#include "DuneRL.h"

#include "Tile.h"

Inventory::Inventory(Rect rect,Player *player) : Menu(rect)
{
    this->player = player;
    
	borderStyle = Border_Single;
	getCentreLabel()->setString("Items");
	getCentreLabel()->setColour(Colour::red());
    
//    groundLabel = new Label("Ground");
//	groundLabel->setFrame(Rect(16,12,100,40));
//    Window::add(groundLabel);
	
//	LabelValue<bool,Object> *devLabel = new LabelValue<bool,Object>(std::string("Debug"),&(DEV));
//	devLabel->setFrame(Rect(16,18+24,100,40));
//	devLabel->setString("Debug");
//	add(devLabel);
	
//	Label *exitLabel = new Label("Exit");
//	exitLabel->setFrame(Rect(16,18+36,100,40));
//	add(exitLabel);
}

Objects Inventory::groundItems()
{
    Objects ground;
    Objects *objs = player->getParent()->getObjects();
    if(objs)
    {
        foreachp(Objects, o, objs)
        {
            Object *object = (*o);
            if(object->canBeCarried()|object->_flags.consumable)
            {
                ground.push_back(object);
            }
        }
    }
    return ground;
}

std::string Inventory::describeObject(Object *object)
{
    std::string equipped = "";
    if(player->objectIsEquipped(object))
        equipped = " #0f0(equipped)%";
    else if((object->_flags.stackable == YES) && (object->count > 1))
    {
        return stringFormat(object->stackName,object->count);
    }
    
    return stringFormat("%s%s",object->name.c_str(),equipped.c_str());
}

void Inventory::open()
{
    Objects ground = groundItems();
    //int groundSize = ground.size();
    
    rect.Height = (12 * numberOfItems()) + 12 + 12 + 24;
    setup();
    
    // empty all current displays
    foreach(Displays,d,displays)
    {
        delete (*d);
    }
    displays.clear();
    
    int i = 0;
    Objects *inv = player->getInventory();
    if(inv != NULL)
    {    
        foreachp(Objects, o, inv)
        {
            std::string desc = describeObject(*o);
            Label *itemLabel = new Label(desc);
            itemLabel->setFrame(Rect(18,24+(12*i),rect.Width,12));
            add(itemLabel);
            i++;
            
            printf("inv: %s\n",desc.c_str());
        }
    }

    if(!ground.empty())
    {
        // ground label
        int j = i; // save ground and place label below the others, this makes ground not selectable
        i++;
        
        foreach(Objects, o, ground)
        {
            std::string desc = describeObject(*o);
            Label *itemLabel = new Label(desc);
            itemLabel->setFrame(Rect(18,24+(12*i),rect.Width,12));
            add(itemLabel);
            i++;
            
            printf("inv: %s\n",desc.c_str());
        }
        
        Label *itemLabel = new Label("Ground:");
        itemLabel->setFrame(Rect(18,24+(12*j),rect.Width,12));
        itemLabel->setColour(Colour(0.3f,0.3f,0.3f));
        add(itemLabel);
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
    
    Objects ground = groundItems();
    int groundSize = ground.size();
    
	return inv->size() + groundSize;
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

Object *Inventory::getSelectedObject()
{
    int i=0;
    
    
    Objects *inv = player->getInventory();
    if(inv)
    {
        foreachp(Objects, o, inv)
        {
            if(i==selectedIndex)
                return (*o);
            i++;
        }
    }
    Objects ground = groundItems();
    if(!ground.empty())
    {
        foreach(Objects, o, ground)
        {
            if(i==selectedIndex)
                return (*o);
            i++;
        }
    }
    
    
    return NULL;
}

void Inventory::dropSelected()
{
    Object *object = getSelectedObject();
    player->dropInventoryObject(object);
    //close();
    open();
}

void Inventory::pickupSelected()
{
    Object *object = getSelectedObject();
    player->addObjectToInventory(object);
    //close();
    open();
}

void Inventory::equipSelected()
{
    Object *object = getSelectedObject();
    player->equip(object);
    //close();
    open();
}

void Inventory::unequipSelected()
{
    Object *object = getSelectedObject();
    player->unequip(object);
    //close();
    open();
}

void Inventory::consumeSelected()
{
    Object *object = getSelectedObject();
    if(player->consume(object))
    {
        close();
        DuneRL::shared->playerEndedTurn();
    }
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
            case SDLK_e: //equip
                equipSelected();
                break;
            case SDLK_u: //equip
                unequipSelected();
                break;
            case SDLK_q: //consume
                consumeSelected();
                break;
            case SDLK_d: //drop
                dropSelected();
                break;
            case SDLK_p: //pickup
                pickupSelected();
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