/*
	queue.h
	Queuelogic, handling orders
	Sivert and Eirik - 2015
*/
#ifndef __queue_h__
#define __queue_h__

#include <stdbool.h>
#include "elev.h"

struct orderL{
	bool up[numberOfFloors];
	bool command[numberOfFloors];
	bool down[numberOfFloors];
};

void initializeQueue(void);

void order(elev_button_type_t button, int floor);
 
void deleteOrder(int floor, elev_motor_direction_t dir);

void deleteAllOrders(void);

//Returns index of next floor to reach, -1 if queue is empty
int getNextFloor(int floor, elev_motor_direction_t dir);

#endif //__queue_h__
