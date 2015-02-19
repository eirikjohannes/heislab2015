
#ifndef __queue_h__
#define __queue_h__

#include <stdbool.h>
#include "elev.h"



struct orderL{
	bool up[4];
	bool command[4];
	bool down[4];
};

void initializeQueue(void);
void printOrders();

void order(elev_button_type_t button, int floor);

void deleteOrder(int floor, elev_motor_direction_t dir);
/*
Deletes all orders in case of stopBtn pushed
*/
void deleteAllOrders(void);
/*
Returns the order on top of queue
*/
int getNextFloor(int floor, elev_motor_direction_t dir);



#endif //__queue_h__
