//
//  DeathMenu.h
//  Roguelike
//
//  Created by Daniel Brooker on 12/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef DEATHMENU_INCLUDE_H
#define DEATHMENU_INCLUDE_H

#include "Menu.h"
#include "LabelValue.h"
#include <string>

#include "Player.h"

class DeathMenu : public Menu
{
    
public:
    DeathMenu(Rect rect,Player *player);
    
    virtual int numberOfItems();
    virtual void didSelectItem(int index);
};

#endif
