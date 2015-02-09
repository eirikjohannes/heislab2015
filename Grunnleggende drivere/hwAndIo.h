
#ifndef __HW_IO_H__
#define __HW_IO_H__

#include "elev.h"

setMotorDirection(elev_motor_direction_t dir);

void checkButtons(void);

void checkStopButton(void);

void arriveAtFloor(void);


#endif //__HW_IO_H__
