#include "hwAndIo.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(){
	initializeQueue();
	order(BUTTON_CALL_UP,2);
	order(BUTTON_CALL_DOWN,1);
	order(BUTTON_COMMAND,3);
	order(BUTTON_COMMAND,2);
	order(BUTTON_COMMAND,1);
	order(BUTTON_COMMAND,0);
	
	printOrders();
	deleteAllOrders();
	printOrders();

	return 0;
}