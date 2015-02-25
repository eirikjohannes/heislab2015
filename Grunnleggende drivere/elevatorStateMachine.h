
#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#include <stdbool.h>

#include "elev.h"
#include "hwAndIo.h"

typedef enum State{
	movingUp,
	movingDown,
	stationary,
	stopped
}StateT;

typedef enum Event{
	stop,
	stationaryNoOrder,
	arrivesAtDesiredFloor,
	desiredFloorAbove,
	desiredFloorBelow
}EventT;

struct stateInfoT{
	StateT state;
	int floorToReach, currentFloor;
	elev_motor_direction_t currentDir;
	elev_motor_direction_t currentMotorDir;
};

//initializes the elevator from scratch
void initializeElevator(void);

int getFloorToReach(void);

int getLastFloor(void);

elev_motor_direction_t getDesiredDir(void);

elev_motor_direction_t getMotorDir(void);

//sets the state needed to handle event
void setEvent( EventT input);

StateT getState(void);

//updates currentFloor, floorToReach, stopstatus and sets floor indicator
void updateFloorStatus(int floorSensorSignal);







#endif //__INCLUDE_STATEMACHINE_H__
