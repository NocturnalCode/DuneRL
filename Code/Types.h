/*
 *  Types.h
 *  Roguelike
 *
 *  Created by Daniel on 11/02/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */
 
#ifndef TYPES_H_INC
#define TYPES_H_INC 

#include <map>
#include <list>
#include <vector>
#include <string>
#include <cmath>

#include "SDL/SDL.h"

class Object;
class Window;
class Roguelike;
class Monster;
class Effect;

typedef std::list<std::string> Strings; 
typedef std::list<Window*> Windows;
typedef std::list<Object*> Objects;
typedef std::list<Monster*> Monsters;
typedef std::list<Effect*> Effects;

typedef bool (*KeyAction)(void);
typedef std::map<SDLKey,KeyAction> KeyMap;

typedef std::map<std::string, Object *> ObjectMap;

template < class Class, typename ReturnType>
class CallBack
{
public:
    
    typedef ReturnType (Class::*Method)(void);
    
    CallBack(Class* _class_instance, Method _method)
    {
        class_instance = _class_instance;
        method        = _method;
    };
    
    ReturnType operator()(void)
    {
        return (class_instance->*method)();
    };
    
    ReturnType execute()
    {
        return (class_instance->*method)();
    };
    
private:
    
    Class*  class_instance;
    Method  method;
};

#define YES 1
#define NO 0

#define ARRAY2D(i_i,j_j,w_w) (i_i+(w_w*j_j))
#define foreach(type,counter,collection) for(type::iterator counter = collection.begin(); counter != collection.end(); counter++)
#define foreachp(type,counter,collection) for(type::iterator counter = collection->begin(); counter != collection->end(); counter++)
#define rforeach(type,counter,collection) for(type::reverse_iterator counter = collection.rbegin(); counter != collection.rend(); counter++)
#define rforeachp(type,counter,collection) for(type::reverse_iterator counter = collection->rbegin(); counter != collection->rend(); counter++)
#define DEV (Roguelike::dev)

#define HAS_MASK(var,mask) (mask == (var & mask))
#define NOT_MASK(var,mask) (!(mask == (var & mask)))

#define MAX(x,y) ( (x>y)?x:y )
#define MIN(x,y) ( (x<y)?x:y )

#endif /* TYPES_H_INC */