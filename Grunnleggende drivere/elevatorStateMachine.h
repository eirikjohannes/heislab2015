
#ifndef __INCLUDE_STATEMACHINE_H__
#define __INCLUDE_STATEMACHINE_H__

#include "elev.h"
#include <stdbool.h>
#include "hwAndIo.h"

typedef enum state{
	movingUp,
	movingDown,
	stationary,
	stopped,
	numberOfStates
} stateT;

struct stateInfoT{
	stateT state;
	int floorToReach, currentFloor;
	elev_motor_direction_t currentDir;
	elev_motor_direction_t currentMotorDir;
};
 
void initializeStateMachine(void);

void setEvent();

struct stateInfoT getState(void);





#endif //__INCLUDE_STATEMACHINE_H__
