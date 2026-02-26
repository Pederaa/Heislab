#pragma once
#include <unistd.h>
#include "Elevator_controller.h"
#include "elevio.h"

typedef struct{
    int current_floor;
    int direction;
    bool door_open;
    bool stopPressed;
    bool at_floor;
    MotorDirection direction;
} Elevator;

void move(Elevator* e, MotorDirection dir);
void stop();
void Elevator_open_door(Elevator* e);
bool floor_reached();