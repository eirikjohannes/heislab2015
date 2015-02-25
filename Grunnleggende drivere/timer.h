/*
	timer.h
	Simple 3 second timer
	Sivert and Eirik - 2015
*/
#ifndef __timer_h__
#define __timer_h__

#include <stdbool.h>

//Returns true if 3 secons has passed, false otherwise
bool timerIsDone(void);

//Starts timer
void startTimer(void);

#endif //__timer_h__
