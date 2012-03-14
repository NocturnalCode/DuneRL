//
//  Inventory.h
//  Roguelike
//
//  Created by Daniel Brooker on 14/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef INVENTORY_INCLUDE_H
#define INVENTORY_INCLUDE_H

#include "Menu.h"
#include "Player.h"

class Inventory : public Menu
{
    Player *player;
public:
    Inventory(Rect rect,Player *player);
    
    virtual int numberOfItems();
    virtual void didSelectItem(int index);
    
    virtual void open();
    virtual void close();
    virtual bool wantsEvents();
};


#endif /* INVENTORY_INCLUDE_H */
