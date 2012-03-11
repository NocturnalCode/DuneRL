/*
 *  Player.cpp
 *  DuneRL
 *
 *  Created by Daniel on 12/03/12.
 *  Copyright 2012 nocturnalcode.com. All rights reserved.
 *
 */

#include "Player.h"

Player::Player() : Monster(new Ascii(64,Colour::red(), Colour::clear()))//Monster(new Ascii(64,1.0,0,0))
{
	behaviour = BehaviourNone;
    sight = 40;
    name = "Player";
    
}