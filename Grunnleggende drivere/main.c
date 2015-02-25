#include "elev.h"
#include "channels.h"
#include "io.h"
#include "elevatorStateMachine.h"


int main() 
{

	// Initialize hardware
	initializeElevator();

	while (1)
	{
		int floorSensor = getFloor(); //buffer
		
		checkButtons();
		checkStopButton();
		updateFloorStatus(floorSensor);

		//if the stop button has been pushed
		if(getState() == stopped)
			setEvent(stop);

		//While we dont have any orders, and the elevator isnt stopped by the stop button
		else if(getFloorToReach() == -1 )
			setEvent(stationaryNoOrder);

		//Arrives at the correct floor
		else if(getLastFloor() == getFloorToReach() && floorSensor != -1)
			setEvent(arrivesAtDesiredFloor);

		//If floor to reach is above the current floor
		else if(getFloorToReach() > getLastFloor() && getFloorToReach() != -1)
			setEvent(desiredFloorAbove);

		//if the floor to reach is below the current floor
		else if(getFloorToReach() < getLastFloor() && getFloorToReach() != -1)
			setEvent(desiredFloorBelow);
	}
	return 0;
}

