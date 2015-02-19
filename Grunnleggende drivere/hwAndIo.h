
#ifndef __HW_IO_H__
#define __HW_IO_H__

#include "elev.h"
#include <stdbool.h>

static bool stopButtonPushed=false;

void setMotorDirection(elev_motor_direction_t dir);

void checkButtons(void);

bool checkStopButton(void);

void arriveAtFloor(void);


#endif //__HW_IO_H__
