
#ifndef __queue_h__
#define __queue_h__

#include <stdbool.h>



struct queueNode{
	int floor;
	elev_motor_direction_t relativeDir;
	struct queueNode* previous;
	struct queueNode* next;
};


void initializeQueue(void);

void orderIn(int floor, int currentFloor, int currentDir);

void orderOut(int floor, elev_motor_direction_t dir, int currentFloor, elev_motor_direction_t currentDir);

void deleteOrder(void);

/*
Deletes all orders in case of stopBtn pushed
*/
void deleteAllOrders(void);

/*
Returns the order on top of queue
*/
int getCurrentOrder(int floor, elev_motor_direction_t dir);



#endif //__queue_h__
