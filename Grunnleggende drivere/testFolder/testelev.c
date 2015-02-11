// Wrapper for libComedi Elevator control.
// These functions provides an interface to the elevators in the real time lab
//
// 2007, Martin Korsgaard


//#include "channels.h"
#include "testelev.h"
//#include "io.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>  

// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3
/*
static const int lamp_channel_matrix[N_FLOORS][N_BUTTONS] = {
    {LIGHT_UP1, LIGHT_DOWN1, LIGHT_COMMAND1},
    {LIGHT_UP2, LIGHT_DOWN2, LIGHT_COMMAND2},
    {LIGHT_UP3, LIGHT_DOWN3, LIGHT_COMMAND3},
    {LIGHT_UP4, LIGHT_DOWN4, LIGHT_COMMAND4},
};


static const int button_channel_matrix[N_FLOORS][N_BUTTONS] = {
    {BUTTON_UP1, BUTTON_DOWN1, BUTTON_COMMAND1},
    {BUTTON_UP2, BUTTON_DOWN2, BUTTON_COMMAND2},
    {BUTTON_UP3, BUTTON_DOWN3, BUTTON_COMMAND3},
    {BUTTON_UP4, BUTTON_DOWN4, BUTTON_COMMAND4},
};
*/
int elev_init(void) {
     printf("\nInitiated elevator\n");
    // Return success.
    return 1;
}

void elev_set_motor_direction(elev_motor_direction_t dirn) {
    if (dirn == 0){
        printf("\nMotor not running\n");
    } else if (dirn > 0) {        
        printf("\nMotor running up\n");
    } else if (dirn < 0) {
        printf("\nMotor running down\n");
    }
}

void elev_set_door_open_lamp(int value) {
    if (value)
        
        printf("\n Door open light lit\n");
    else
        
        printf("\nDoor open light not lit\n");
}

int elev_get_obstruction_signal(void) {
//    return io_read_bit(OBSTRUCTION);
    return 0;
}

int elev_get_stop_signal(void) {
    int x=0;
    printf("\nShould stopbutton be bushed? 1/0\n");
    scanf("%d",&x);
    return x;
  //  return io_read_bit(STOP);
}

void elev_set_stop_lamp(int value) {
    if (value)
        printf("\nStop lamp lit\n");
    else
        printf("\nStop lamp not lit\n");
}

int elev_get_floor_sensor_signal(void) {
    int x=0;
    printf("\nWhich floor to get? (3,2,1,0,-1(error))\n");
    scanf("%d",&x);
    return x;
}

void elev_set_floor_indicator(int floor) {
}

int elev_get_button_signal(elev_button_type_t button, int floor) {
    /*assert(floor >= 0);
    assert(floor < N_FLOORS);
    assert(!(button == BUTTON_CALL_UP && floor == N_FLOORS - 1));
    assert(!(button == BUTTON_CALL_DOWN && floor == 0));
    assert(button == BUTTON_CALL_UP || button == BUTTON_CALL_DOWN || button == BUTTON_COMMAND);
    */
    int x=0;
    printf("\nShould button x on floor %d be pushed\n", floor);
    scanf("%d",&x);
    if (x)
        return 1;
    else
        return 0;
}

void elev_set_button_lamp(elev_button_type_t button, int floor, int value) {
    printf("\n Sets button lamp of some sort\n");
}
