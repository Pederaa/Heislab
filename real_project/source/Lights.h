#pragma once

typedef struct {
    int floor_lights[4];
    int panel_lights[4];
    int opp_lights[4];
    int ned_lights[4];
} Lights;

void lights_setfloorIndicator(Lights *lights, int floor, int value);
void lights_setOrderlIght(Lights *lights, int floor, MotorDirection dir, int value);