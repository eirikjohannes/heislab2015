
#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#include "testelev.h"
#include <stdbool.h>
#include "hwAndIo.h"

typedef enum stateDir{
	movingUp    =1,
	movingDown  =-1,
	stationary  =0,
	initialize  =-2,
	stopped     =2
} stateDirT;

struct state{
	stateDirT direction;
	int floorToReach, currentFloor;
	bool doorStatus; //Open=1, closed=0
	elev_motor_direction_t currentDir;
}stateT;
 
void initializeStateMachine(void);
void setEvent(stateT desiredState, int currentFloor, elev_motor_direction_t currentDir,queueNode *currentOrderBeingExecuted);

stateT& getState(void);





#endif //__INCLUDE_STATEMACHINE_H__
