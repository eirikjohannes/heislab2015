
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
//#include "elev.h"
#include <stdbool.h>




struct queueNode firstNode;

void checkForDirectionAndFloorMatch(struct queueNode *order) //Checks if the order is already in the queue
{
	bool floorMatch = false, directionMatch = false;
	struct queueNode * tempNode= &firstNode;
	while(tempNode->previous!=NULL){
		tempNode=tempNode->previous;
		
		if(order->floor==tempNode->floor)
		{
			floorMatch = true;
		}	
		if(order->relativeDir == tempNode->relativeDir)
		{
			directionMatch = true;
		}
	}
	if(floorMatch && directionMatch)
	{			
		free(order); //deletes the order trying to be placed	
		
	}
	else
	{
		pushQueue();
	}
	

}

void pushQueue(){

}

void popQueue(){

}


void deleteOrder(struct queueNode * order)
{
	struct queueNode * tempOrder = order->next;
	tempOrder->previous = order->previous;
	//Erstattet order sin posisjon med temporder
	free(order);
	printf("\nOrder deleted\n");
}

void initializeQueue(void)
{
	firstNode.floor=0;
	firstNode.relativeDir=DIRN_STOP;
	firstNode.previous= NULL;
	firstNode.next= NULL;
	
	orderIn(2,2,DIRN_STOP); //2 is imaginary number
	orderIn(3,2,DIRN_STOP);
	
	
}

void orderIn(int floor, int currentFloor, elev_motor_direction_t currentDir){
	struct queueNode * newOrder=malloc(sizeof(struct queueNode));
	newOrder->floor=floor;
	if (firstNode.previous==NULL){ //checks if queue is empty
		firstNode.previous=newOrder;
		newOrder->next=&firstNode;	
	}
	else
	{
		checkForDirectionAndFloorMatch(newOrder);
	}

	
}

void orderOut(int floor, elev_motor_direction_t dir, int currentFloor, elev_motor_direction_t currentDir)
{
	struct queueNode * newOrder=malloc(sizeof(struct queueNode));
	newOrder->floor=floor;
	newOrder->relativeDir=dir;
	if (firstNode.previous==NULL){ //checks if queue is empty
		firstNode.previous=newOrder;
		newOrder->next=&firstNode;	
	}
	else
	{
		checkForDirectionAndFloorMatch(newOrder);
	}

}
/*
Deletes all orders in case of stopBtn pushed
*/
void deleteAllOrders(void){
	
}

/*
Returns the order on top of queue
*/
int getCurrentOrder(int floor, elev_motor_direction_t dir){
	struct queueNode * tempNode= &firstNode;
	while(tempNode->previous!=NULL){
		tempNode=tempNode->previous;	
	}
	return tempNode->floor;
}

