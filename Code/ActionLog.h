//
//  ActionLog.h
//  Roguelike
//
//  Created by Daniel Brooker on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#ifndef ACTIONLOG_H_INC
#define ACTIONLOG_H_INC

#include "Window.h"
#include <vector>

class ActionLog : public Window
{
protected:
    
    std::vector<int> age;
    int turn;
    
    bool wantsEvents();
public:
    ActionLog(Rect rect);
    
    void display();
};

#endif /* ACTIONLOG_H_INC */
