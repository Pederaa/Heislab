#pragma once
#include <unistd.h>
#include "driver/elevio.h"
#include <stdbool.h>
#include <time.h>

typedef struct{
    int current_floor;
    bool door_open;
    bool at_floor;
    MotorDirection direction;
    time_t door_open_time;
} Elevator;

void Elevator_move(Elevator* e, MotorDirection dir);
void Elevator_stop(Elevator* e);
void Elevator_open_door(Elevator* e);
void Elevator_close_door(Elevator* e);
Elevator Elevator_initialize();
bool Elevator_floor_reached();
void Elevator_update_position(Elevator* e);
bool Elevator_handle_stop_button(Elevator* e);