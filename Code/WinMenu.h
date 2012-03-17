//
//  WinMenu.h
//  Roguelike
//
//  Created by Daniel Brooker on 17/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef WINMENU_INCLUDE_H
#define WINMENU_INCLUDE_H

#include "Menu.h"
#include "LabelValue.h"
#include <string>

#include "Player.h"

class WinMenu : public Menu
{
    
public:
    WinMenu(Rect rect,Player *player);
    
    virtual int numberOfItems();
    virtual void didSelectItem(int index);
};

#endif /* WINMENU_INCLUDE_H */