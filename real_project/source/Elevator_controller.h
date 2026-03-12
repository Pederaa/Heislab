#pragma once
#include <stdbool.h>
#include "Elevator.h"
#include "Lights.h"

typedef struct {
    int target_floor;
} Elevator_controller;

bool elevator_controller_should_stop(int floor, bool at_floor, Elevator_controller ec);
void elevator_controller_new_target_floor(Elevator_controller* ec, int target);
void elevator_controller_choose_dir(Elevator_controller* ec, Elevator *e);
Elevator_controller Elevator_controller_initialize();
void elevator_controller_change_target_floor(Elevator_controller* ec, Elevator* e, Lights* lights);
bool elevator_controller_floor_has_order(Lights* lights, int floor);