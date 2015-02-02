#ifndef __INCLUDE_WRAPPER_H__
#define __INCLUDE_WRAPPER_H__



int elevInit(void);

typedef enum tag_elev_lamp_type { 
    BUTTON_CALL_UP = 0,
    BUTTON_CALL_DOWN = 1,
    BUTTON_COMMAND = 2
} elev_button_type_t;

typedef enum elevMotorDirection { 
    DOWN = -1,
    STOP = 0,
    UP = 1
} motorDirectionT;

void setMotorDirection(motorDirectionT dir);

void setDoorOpenLamp(int value);

int checkStopButton(void);

void setStopLamp(int value);

int getFloor(void);

void setFloorIndicator(int floor);

int getButton(elev_button_type_t button, int floor);

void setButtonLamp(elev_button_type_t button, int floor, int enable)

#endif