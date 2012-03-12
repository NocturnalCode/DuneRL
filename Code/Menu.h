/*
 *  Menu.h
 *  Roguelike
 *
 *  Created by Daniel on 20/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Window.h"
#include <string>

#ifndef MENU_H
#define MENU_H

class Menu : public Window
{
	protected:
		int selectedIndex;
		Display *selected;
       
    
	public:
		Menu(Rect rect);
	
        bool isOpen;
    
        void open();
		virtual void close();
		virtual bool handleEvents(SDL_Event *event);
		virtual int numberOfItems();
		virtual void didSelectItem(int index);
		virtual void add(Display *displayable);
		virtual bool wantsEvents();
		virtual void changeSelection();
};

#endif /* MENU_H */ 