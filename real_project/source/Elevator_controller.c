#include "Elevator_controller.h"


bool elevator_controller_should_stop(int floor, Elevator_controller ec){
    return (floor == ec.target_floor);
};

void elevator_controller_new_target_floor(int target, Elevator_controller* ec){
    ec->target_floor = target;
};

//choose_dir? 