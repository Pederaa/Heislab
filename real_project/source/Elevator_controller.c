#include "Elevator_controller.h"
#include "elevio.h"
#include "Elevator.h"
#include <stdbool.h>


bool elevator_controller_should_stop(int floor, Elevator_controller ec){
    return (floor == ec.target_floor);
};

void elevator_controller_new_target_floor(Elevator_controller* ec, int target){
    ec->target_floor = target;
};

MotorDirection elevator_controller_choose_dir(Elevator_controller* ec, Elevator* e){
    if(e->current_floor == 0){
        e->direction = DIRN_UP;
    }
    else if(e->current_floor == N_FLOORS-1){
        e->direction = DIRN_DOWN;
    }
    
    else if (ec->target_floor > e->current_floor){
        e->direction = DIRN_UP;
    } 
    else if (ec->target_floor < e->current_floor){
        e->direction = DIRN_DOWN;
    } 
    else {
        e->direction = DIRN_STOP;
    }
} 

//lag logikk for valg av target_floor