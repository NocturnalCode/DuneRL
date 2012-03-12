/*
 *  Menu.cpp
 *  Roguelike
 *
 *  Created by Daniel on 20/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Menu.h"
#include "LabelValue.h"

Menu::Menu(Rect rect) : Window(rect)
{
	selectedIndex = 0;
}

void Menu::open()
{
	isOpen = true;
    SDL_EnableKeyRepeat(0, 0);
}

void Menu::close()
{
	isOpen = false;
	parent->remove(this);
    SDL_EnableKeyRepeat(25, 50);
}

void Menu::add(Display *displayable)
{
	if(displays.size()==0)
		displayable->setSelected(true);
	else
		displayable->setSelected(false);
	Window::add(displayable);
}

bool Menu::wantsEvents()
{
	return numberOfItems() > 0;
}

int Menu::numberOfItems()
{
	return 0;
}

void Menu::changeSelection()
{
	int i=0;
	//printf("Changing selected to index %d\n",selectedIndex);
	for(Displays::iterator d = displays.begin(); d != displays.end(); d++,i++)
	{
		if(i==selectedIndex)
			selected = (*d);
		(*d)->setSelected(i==selectedIndex);
	}
}

void Menu::didSelectItem(int index)
{
	printf("Selected item: %d",index);
}

bool Menu::handleEvents(SDL_Event *event)
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