//Wrapper for the wrapper to use nice syntax

#include "elev.h"

int elevInit(void)
{
	return elev_init();
}

void setMotorDirection(motorDirectionT dir){
	elev_set_motor_direction(dir);
}

void setDoorOpenLamp(int value){
	elev_set_door_open_lamp(value);
}

//int getObstructionSignal()

int checkStopButton(void)
{
	return elev_get_stop_signal(void);
}

void setStopLamp(int value){
	elev_set_stop_lamp(value);
}

int getFloor(void){
	int i = elev_get_floor_sensor_signal(void);
	switch (i){
	case -1: return -1;
	break;
	default: return i+1;
}
}

void setFloorIndicator(int floor){
	elev_set_floor_indicator(floor);
}

int getButton(elev_button_type_t button, int floor){
	return elev_get_button_signal(button,floor);
}

void setButtonLamp(elev_button_type_t button, int floor, int enable){
	elev_set_button_lamp(button, floor, enable);
}

