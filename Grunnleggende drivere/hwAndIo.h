/*
	hwAndIo.h
	Hardware and input/output interface
	Sivert and Eirik - 2015
*/
#ifndef __HW_IO_H__
#define __HW_IO_H__

#include <stdbool.h>
#include "elev.h"

//returns index of current floor(0-(numberOfFloors-1)),
// returns -1 if between floors
int getFloor(void);

void setMotorDirection(elev_motor_direction_t dir);

void checkButtons(void);

bool checkStopButton(void);

bool getStopButtonSignal(void); //buffer
 
void arriveAtFloor(void);


#endif //__HW_IO_H__
