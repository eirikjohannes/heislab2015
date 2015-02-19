
#include "elev.h"
#include "channels.h"
#include "io.h"
#include "elevatorStateMachine.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    

    setMotorDirection(DIRN_DOWN);
    while(getFloor()!=0){
        printf("Getfloor returnerer: %d\n",getFloor());
    }
    setMotorDirection(DIRN_STOP);
    initializeStateMachine();
    printf("\nElevator is now initialized\n");
    while (1) {
        setEvent();

    }

    return 0;
}
