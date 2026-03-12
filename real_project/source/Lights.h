#pragma once
#include "driver/elevio.h"
#include "Elevator.h"

typedef struct {
    int floor_lights[N_FLOORS];
    int panel_lights[N_FLOORS];
    int opp_lights[N_FLOORS];
    int ned_lights[N_FLOORS];
} Lights;

void lights_initilize(Lights *lights);
void lights_setfloorIndicator(Lights *lights, int floor, int value);
void lights_setOrderlIght(Lights *lights, int floor, MotorDirection dir, int value);
void lights_setPanellIght(Lights *lights, int floor, int value);
void lights_updateLights(Lights *lights, Elevator *e);
void lights_clear_orders_at_floor(Lights* lights, Elevator* e);