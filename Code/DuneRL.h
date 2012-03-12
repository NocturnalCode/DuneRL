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

class Player;

class DuneRL : public Roguelike
{
protected:
    Player *player;

    DeathMenu *dmenu;
    
    
public:
    DuneRL();
    ~DuneRL();

    virtual void init_world();

    std::string getTurnLog();
    void deathMenu();
    
    static DuneRL *shared;
};

#endif /* DUNERL_H_INC */