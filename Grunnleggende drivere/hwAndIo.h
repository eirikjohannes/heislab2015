
#ifndef __HW_IO_H__
#define __HW_IO_H__

#include <stdbool.h>

#include "elev.h"

//returns index of current floor(0-(numberOfFloors-1)),
// returns -1 if between floors
int getFloor(void);

//wraps function called elev_set_motor_direction (didnt like the case-style)
void setMotorDirection(elev_motor_direction_t dir);

//checks every single orderbutton and asigns orders to queue
void checkButtons(void);

//checks if stop button is pushed
bool checkStopButton(void);

bool getStopButtonSignal(void); //buffer

//opens doors for 3 seconds, also checks if stop button or any orderbutton is pushed 
void arriveAtFloor(void);


#endif //__HW_IO_H__
