#include "timer.h"

#include <time.h>


static time_t timeStarted; 
/*
Checks if three seconds have passed
*/
bool timerIsDone(void)
{
	if((time(NULL)-timeStarted)>3)
	{
		return true;
		
	}
	return false;
}

void startTimer(void)
{
	timeStarted=time(NULL);
}
