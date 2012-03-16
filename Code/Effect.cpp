//
//  Effect.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Effect.h"

Effect::Effect(int d,Object *object,int effectID)
{
    eid = effectID;
    duration = 0;
    addDuration(d);
    this->object = object;
}

int Effect::getDuration()
{
    return duration;
}

void Effect::addDuration(int d)
{
    duration += d;
}

void Effect::update()
{
    duration--;
}

void Effect::onAdded()
{
}

void Effect::onRemoved()
{
}

void Effect::onFinished()
{
}

bool Effect::isCompleted()
{
    return duration <= 0;
}