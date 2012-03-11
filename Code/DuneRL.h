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

class Player;

class DuneRL : public Roguelike
{
	protected:
		Player *player;
	public:
		DuneRL();
		~DuneRL();
		virtual void init_world();
};

#endif /* DUNERL_H_INC */