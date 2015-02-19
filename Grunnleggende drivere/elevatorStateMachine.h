
#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#include "testelev.h"
#include <stdbool.h>
#include "hwAndIo.h"

typedef enum state{
	movingUp,
	movingDown,
	stationary,
	stopped,
	numberOfStates
} stateT;

struct stateInfo{
	stateT state;
	int floorToReach, currentFloor;
	elev_motor_direction_t currentDir;
}stateInfoT;
 
void initializeStateMachine(void);

void setEvent();

stateT getState(void);





#endif //__INCLUDE_STATEMACHINE_H__
