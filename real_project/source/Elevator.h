#pragma once
#include <unistd.h>
#include "driver/elevio.h"
#include <stdbool.h>

typedef struct{
    int current_floor;
    bool door_open;
    bool stopPressed;
    bool at_floor;
    MotorDirection direction;
} Elevator;

void Elevator_move(Elevator* e, MotorDirection dir);
void Elevator_stop();
void Elevator_open_door(Elevator* e);
bool Elevator_floor_reached();