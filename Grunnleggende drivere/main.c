
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
    initializeQueue();

    printf("Press STOP button to stop elevator and exit program.\n");

    setMotorDirection(DOWN);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (getFloor() == N_FLOORS) {
            setMotorDirection(DOWN);
        } else if (getFloor() == 1) {
            setMotorDirection(UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (checkStopButton()) {
            setMotorDirection(STOP);
            break;
        }
    }

    return 0;
}
