/*
	queue.c
	Queuelogic, handling orders
	Sivert and Eirik - 2015
*/
	
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "queue.h"

static struct orderL orderList;

void printOrders(){
	printf("Up, down, command\n");
	for (int i=0; i<numberOfFloors;i++){
		printf(" %d, %d, %d \n",orderList.up[i], orderList.down[i],orderList.command[i]);
	}
}
void initializeQueue(void){
	for (int i=0; i<numberOfFloors;i++){
		orderList.up[i]=0;
		orderList.down[i]=0;
		orderList.command[i]=0;
	}
	printf("First init\n");
	printOrders();
}


void deleteOrder(int floor, elev_motor_direction_t dir)
{
	switch(dir){
		case DIRN_UP:
			orderList.up[floor]=0;
			orderList.command[floor]=0;
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
			if(floor!=(numberOfFloors-1)&&floor!=0)
			{
				orderList.down[floor]=0;
				elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
			}
			break;
		case DIRN_DOWN:
			orderList.down[floor]=0;
			orderList.command[floor]=0;
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
			if(floor!=0&&floor!=(numberOfFloors-1))
			{
				orderList.up[floor]=0;
				elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
			}			
			break;
		case DIRN_STOP:
			orderList.command[floor]=0;	
			elev_set_button_lamp(BUTTON_COMMAND,floor,0);
			if(floor!=0||floor!=(numberOfFloors-1))
			{
				elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
				orderList.down[floor]=0;
				orderList.up[floor]=0;
				elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
			}
			break;
	}
}

//Floor is between 0 and numberOfButtons
void order(elev_button_type_t button, int floor){
	switch (button){
		case BUTTON_CALL_UP:
			if (!(orderList.up[floor])){
				orderList.up[floor]=1;
				elev_set_button_lamp(button,floor,1);
			}
			break;
		case BUTTON_CALL_DOWN:
			if (!(orderList.down[floor])){
				orderList.down[floor]=1;
				elev_set_button_lamp(button,floor,1);
			}
			break;
		case BUTTON_COMMAND:
			if (!(orderList.command[floor])){
				orderList.command[floor]=1;
				elev_set_button_lamp(button,floor,1);
			}
			break;
	}

}
/*
   Deletes all orders in case of stopBtn pushed
 */
void deleteAllOrders(void){
	for (int i=0; i<numberOfFloors; i++)
	{
		orderList.up[i]=0;
		orderList.down[i]=0;
		orderList.command[i]=0;
		elev_set_button_lamp(BUTTON_COMMAND,i,0);
		for (int j=0; j<numberOfButtons; j++)
		{
			if ((i==0 && j==BUTTON_CALL_DOWN)||
			(i==(numberOfFloors-1)&&j==BUTTON_CALL_UP)) continue;
			elev_set_button_lamp((elev_button_type_t)j,i,0);
		}
	}
}


int getNextFloor(int lastFloor, elev_motor_direction_t dir)
{
	int nextFloor=-1;
	int ctrlVal=numberOfFloors+1;
	//If no values were found in the given direction, check all the other buttons
	switch (dir){
		case DIRN_DOWN:
			for(int i=lastFloor;i>=0;i--){
				if(orderList.down[i] || orderList.command[i])
				{	
					nextFloor=i;
					return nextFloor;
				}
			}
			for(int i=0;i<numberOfFloors;i++)
			{
				if(orderList.down[i]||orderList.command[i]||orderList.up[i])
				{
					if(abs(lastFloor-i)<ctrlVal)
					{
						ctrlVal=abs(lastFloor-i);
						nextFloor=i;
						break;
					}
				}
			}
			break;
		case DIRN_UP:
			for(int i=lastFloor;i<numberOfFloors;i++){
				if(orderList.up[i] || orderList.command[i])
				{
					nextFloor=i;
					return nextFloor;
				}

			}
			for(int i=0;i<numberOfFloors;i++)
			{
				if(orderList.down[i]||orderList.command[i]||orderList.up[i])
				{
					if(abs(lastFloor-i)<ctrlVal)
					{
						ctrlVal=abs(lastFloor-i);
						nextFloor=i;
						break;
					}
				}
			}	
			break;
		case DIRN_STOP:
			for(int i=0;i<numberOfFloors;i++)
			{
				if(orderList.command[i] || orderList.up[i] || orderList.down[i])
				{
					if(abs(lastFloor-i)<ctrlVal)
					{
						ctrlVal=abs(lastFloor-i);
						nextFloor=i;
					}
				}
			}	
	}
	return nextFloor;
}
