/*
	main.c
	Elevatorproject-TTK4125
	Main loop for running elevator
	Controls next "state" for elevator
	Sivert and Eirik - 2015
*/

#include "elev.h"
#include "channels.h"
#include "io.h"
#include "elevatorStateMachine.h"


int main() 
{
	initializeElevator();
	
	while (1)
	{
		int floorSensor = getFloor(); //buffer
		checkButtons();
		checkStopButton();
		updateFloorStatus(floorSensor);

		//if the stop button has been pushed
		if(getState() == stopped)
			setState(stop);
		
		//While we dont have any orders, and the elevator isnt stopped by the stop button
		else if(getFloorToReach() == -1 )
			setState(stationaryNoOrder);

		//Arrives at the correct floor
		else if(getLastFloor() == getFloorToReach() && floorSensor != -1)
			setState(arrivesAtDesiredFloor);

		//If floor to reach is above the current floor
		else if(getFloorToReach() > getLastFloor() && getFloorToReach() != -1)
			setState(desiredFloorAbove);

		//if the floor to reach is below the current floor
		else if(getFloorToReach() < getLastFloor() && getFloorToReach() != -1)
			setState(desiredFloorBelow);
	}
	return 0;
}

