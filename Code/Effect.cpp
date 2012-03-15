//
//  Effect.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "Effect.h"

Effect::Effect(int duration,Object *object)
{
    this->duration = duration;
    this->object = object;
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