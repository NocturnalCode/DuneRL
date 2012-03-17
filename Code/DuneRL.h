/*
 *  DuneRL.h
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#ifndef DUNERL_H_INC
#define DUNERL_H_INC 

#include "Roguelike.h"
#include "DeathMenu.h"
#include "Inventory.h"

class Player;
class ActionLog;

class DuneRL : public Roguelike
{
protected:
    Player *player;

    DeathMenu *dmenu;
    ActionLog *actionLog;
    
    Inventory *inventory;
    
public:
    DuneRL();
    ~DuneRL();

    virtual void init_world();

    void deathMenu();
    void inventoryMenu();
    
    static DuneRL *shared;
};

#endif /* DUNERL_H_INC */