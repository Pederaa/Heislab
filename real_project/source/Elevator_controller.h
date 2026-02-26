#pragma once
#include <stdbool.h>
#include "Elevator.h"

typedef struct {
    int target_floor;
} Elevator_controller;

bool elevator_controller_should_stop(int floor, Elevator_controller ec);

void elevator_controller_new_target_floor(Elevator_controller* ec, int target);

MotorDirection elevator_controller_choose_dir(Elevator_controller* ec, Elevator* e);