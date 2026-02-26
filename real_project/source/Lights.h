#pragma once

#include <elevio.h>

typedef struct {
    int floor_lights[N_FLOORS];
    int panel_lights[N_FLOORS];
    int opp_lights[N_FLOORS];
    int ned_lights[N_FLOORS];
} Lights;

Lights lights_initilize();
void lights_setfloorIndicator(Lights *lights, int floor, int value);
void lights_setOrderlIght(Lights *lights, int floor, MotorDirection dir, int value);
void lights_updateLights(Lights *lights);