
#include "elevWrap.h"
#include "channels.h"
#include "io.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elevInit()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    initializeStateMachine();

    setMotorDirection(DOWN);
    while(getFloor()!=0){
        //do nothing at all
    }
    setMotorDirection(DIRN_STOP)
    while (1) {
        setEvent();

    }

    return 0;
}
