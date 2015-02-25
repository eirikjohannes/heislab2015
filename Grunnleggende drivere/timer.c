#include <time.h>

#include "timer.h"

static time_t timeStarted; 


/*
   Checks if three seconds have passed
 */
bool timerIsDone(void)
{
	if((time(NULL)-timeStarted)>2)
	{
		return true;
	}
	return false;
}

void startTimer(void)
{
	timeStarted=time(NULL);
}
