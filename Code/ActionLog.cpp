//
//  ActionLog.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "ActionLog.h"
#include "Stringer.h"
#include "Roguelike.h"

#include <vector>

ActionLog::ActionLog(Rect rect) : Window(rect)
{
    lastTurn = -1;
    background = false;
    lines = rect.Height/12;
    
    logs = &Roguelike::shared->logs;
    
//    printf("action lines %d \n",lines);
    for(int i=0;i<lines;i++)
    {
        Label *optionsLabel = new Label(stringFormat(""));
        optionsLabel->setFrame(Rect(0,(12*i),rect.Width,40));
        add(optionsLabel);
    }
}

bool ActionLog::wantsEvents()
{
	return false;
}

void ActionLog::display()
{
    int i = logs->size() - lines;
    
    int turn = Roguelike::shared->getCurrentTurn();    
    // update the log
    
    if(turn > lastTurn)
    {
        lastTurn = turn;
        foreach(Displays, display, displays)
        {
            
            Label *label = dynamic_cast<Label *>((*display));
            if(label && i > 0)
            {
                //printf("[%d] log i:%d \n",i,turn);
                std::pair<int, std::string> line = (*logs)[i];
                int t = line.first;
                std::string msg = line.second;
                
                float alpha = 1.0f-(float)(turn-t)/(float)lines;
                //printf("AL[%.1f]: %s\n",alpha,msg.c_str());
                
                label->setString(msg);
                label->setBackgroundColour(Colour(0.0f, 0.0f, 0.0f,alpha));
            }
            i++;
        }
    }
    
    Window::display();
}