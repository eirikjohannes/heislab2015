//#include "hwAndIo.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(){
	initializeQueue();
	order(BUTTON_CALL_UP,2);
	order(BUTTON_CALL_DOWN,1);
	order(BUTTON_COMMAND,3);
	order(BUTTON_COMMAND,2);
	deleteOrder(2,DIRN_STOP);
	printOrders();
	int i = getNextFloor(3,DIRN_STOP);
	printf("\nVi skal til: %d",i+1);



	return 0;
}