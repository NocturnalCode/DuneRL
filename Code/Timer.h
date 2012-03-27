/*
 *  Timer.h
 *  Roguelike
 *
 *	This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
 *  be redestributed without written permission.
 *
 */

#ifndef TIMER_H_INC
#define TIMER_H_INC

#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

#endif /* TIMER_H_INC */