
#ifndef __HW_IO_H__
#define __HW_IO_H__

#include "testelev.h"
#include "queue.h"
#include <stdbool.h>

void setMotorDirection(elev_motor_direction_t dir);

void checkButtons(void);

bool checkStopButton(void);

void arriveAtFloor(void);

int getFloor(void);


#endif //__HW_IO_H__
