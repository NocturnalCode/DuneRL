//
//  ActionLog.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 13/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include "ActionLog.h"
#include "Stringer.h"
#include "DuneRL.h"

ActionLog::ActionLog(Rect rect) : Window(rect)
{
    background = false;
    int lines = rect.Height/12;
    printf("action lines %d \n",lines);
    for(int i=0;i<lines;i++)
    {
        Label *optionsLabel = new Label(stringFormat("Line %d",i));
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
    
    
    // update the log
    rforeach(Displays, display, displays)
    {
        Label *label = dynamic_cast<Label *>((*display));
        if(label)
        {
            
        }
    }
    
    Window::display();
}