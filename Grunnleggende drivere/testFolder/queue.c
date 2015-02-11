
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
//#include "elev.h"
#include <stdbool.h>
#include <math.h>

static struct orderL orderList;
void printOrders();
void initializeQueue(void){
	for (int i=0; i<4;i++){
		orderList.up[i]=0;
		orderList.down[i]=0;
		orderList.command[i]=0;
	}
	printf("First init\n");
	printOrders();
}
void printOrders(){
	printf("Up, down, command\n");
	for (int i=0; i<4;i++){
		printf(" %d, %d, %d \n",orderList.up[i], orderList.down[i],orderList.command[i]);
	}
}
void deleteOrder(int floor, elev_motor_direction_t dir)
{
	//Direction check?
	switch(dir){
		case DIRN_UP:
			orderList.up[floor]=0;
			orderList.command[floor]=0;
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
			break;
		case DIRN_DOWN:
			orderList.down[floor]=0;
			orderList.command[floor]=0;
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
			break;
		case DIRN_STOP:
			orderList.command[floor]=0;
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			break;
	}
}

//Floor is between 0 and 3
void order(elev_button_type_t button, int floor){
	//Checks if order already placed, calls addOrder if not.
	switch (button){
		case BUTTON_CALL_UP:
			if (!(orderList.up[floor])){
				orderList.up[floor]=1;
			}
			break;
		case BUTTON_CALL_DOWN:
			if (!(orderList.down[floor])){
				orderList.down[floor]=1;
			}
			break;
		case BUTTON_COMMAND:
			if (!(orderList.command[floor])){
				orderList.command[floor]=1;
			}
			break;
	}
	printOrders();
}
/*
Deletes all orders in case of stopBtn pushed
*/
void deleteAllOrders(void){
	int floor=4,buttons=3;
	for (int i=0; i<floor; i++)
	{
		orderList.up[i]=0;
		orderList.down[i]=0;
		orderList.command[i]=0;
		elev_set_button_lamp(BUTTON_COMMAND,i,0);
		for (int j=0; j<buttons; j++)
		{
			elev_set_button_lamp((elev_button_type_t)j,i,0);
		}
	}
}

/*
Returns the order on top of queue
*/
int getNextFloor(int lastFloor, elev_motor_direction_t dir)
{
	int nextFloor;
	int ctrlVal=10;
	switch (dir){
		case DIRN_UP:
			for(int i=lastFloor;i<4;i++){
				if(orderList.up[i] || orderList.command[i])
				{
					nextFloor=i;
				}
			}
			break;
		case DIRN_STOP:
			for(int i=0;i<4;i++){
				if(orderList.command[i] || orderList.up[i] || orderList.down[i])
				{
					if(abs(lastFloor-i)<ctrlVal){
						ctrlVal=abs(lastFloor-i);
						nextFloor=i;
					}
				}
			}	
			break;
		case DIRN_DOWN:
			for(int i=lastFloor;i>=0;i--){
					if(orderList.down[i] || orderList.command[i])
					{
						nextFloor=i;
					}
				}
			break;
	}
	return nextFloor;
}

