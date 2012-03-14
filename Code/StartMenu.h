//
//  StartMenu.h
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef STARTMENU_INCLUDE_H
#define STARTMENU_INCLUDE_H

#include "Menu.h"
#include "LabelValue.h"
#include <string>

#include "Player.h"

class StartMenu : public Menu
{
    
public:
    StartMenu(Rect rect,Player *player);
    
    virtual int numberOfItems();
    virtual void didSelectItem(int index);
};

#endif
