#include "Elevator_controller.h"
#include "driver/elevio.h"
#include "Elevator.h"
#include <stdbool.h>
#include "Lights.h"


bool elevator_controller_should_stop(int floor, bool at_floor, Elevator_controller ec){
    if (!at_floor){
        return false;
    }
    
    return (floor == ec.target_floor);
};


void elevator_controller_choose_dir(Elevator_controller* ec, Elevator* e){
    if (ec->target_floor > e->current_floor){
        e->direction = DIRN_UP;
    } 
    else if (ec->target_floor < e->current_floor){
        e->direction = DIRN_DOWN;
    } 
    else if(ec->target_floor == e->current_floor) {
        e->direction = DIRN_STOP;
    } else{
        e->direction = DIRN_STOP;
    }
}
Elevator_controller Elevator_controller_initialize(){
    Elevator_controller ec = {0};
    ec.target_floor = -1;
    return ec;
}

bool elevator_controller_floor_has_order(Lights* lights, int floor){
    return lights->panel_lights[floor] ||
           lights->opp_lights[floor] ||
           lights->ned_lights[floor];


}

void elevator_controller_change_target_floor(Elevator_controller* ec, Elevator* e, Lights* lights){
    if (elevator_controller_floor_has_order(lights, e->current_floor)) {
        ec->target_floor = e->current_floor;
        return;
    }
    if (e->direction == DIRN_UP){
        for (int floor = e->current_floor + 1; floor < N_FLOORS; floor++) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }

        for (int floor = e->current_floor - 1; floor >= 0; floor--) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }
    } else if(e->direction == DIRN_DOWN){
        for (int floor = e->current_floor - 1; floor >= 0; floor--) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }
        for (int floor = e->current_floor + 1; floor < N_FLOORS; floor++) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }

    }
    for (int floor = e->current_floor + 1; floor < N_FLOORS; floor++) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }

        for (int floor = e->current_floor - 1; floor >= 0; floor--) {
            if (elevator_controller_floor_has_order(lights, floor)) {
                ec->target_floor = floor;
                return;
            }
        }
    ec->target_floor = -1;
}
