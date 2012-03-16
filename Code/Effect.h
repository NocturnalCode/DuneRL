//
//  Effect.h
//  Roguelike
//
//  Created by Daniel Brooker on 16/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef EFFECT_INCLUDE_H
#define EFFECT_INCLUDE_H

class Object;

class Effect
{
protected:
    int duration;
    Object *object;
public:
    Effect(int duration,Object *object,int effectID=0);
    
    int eid; // id
    
    virtual void addDuration(int duration);
    virtual int getDuration();
    
    virtual void update();
    virtual void onAdded();
    virtual void onRemoved();
    virtual void onFinished();
    
    virtual bool isCompleted();
};


#endif /* EFFECT_INCLUDE_H */
