#include "Elevator_controller.h"
#include "driver/elevio.h"
#include "Elevator.h"
#include "Lights.h"
#include <stdbool.h>


bool elevator_controller_should_stop(int floor, bool at_floor, Elevator_controller ec){
    if (!at_floor){
        return false;
    }
    
    return (floor == ec.target_floor);
};


void elevator_controller_update_target_floor(Elevator_controller* ec, Elevator* e, Lights* l){
    MotorDirection current_dir = e->direction;

    if (current_dir == DIRN_UP){
        for (int floor=e->current_floor; floor<N_FLOORS; floor++){
            if (l->panel_lights[floor] == 1){
                return floor;
            }
        }

        for (int floor=e->current_floor; floor>=0; floor--){
            if (l->panel_lights[floor] == 1){
                return floor;
            }
        }
    }

    else if (current_dir == DIRN_DOWN){
        for (int floor=e->current_floor; floor>=0; floor--){
            if (l->panel_lights[floor] == 1){
                return floor;
            }
        }
        
        for (int floor=e->current_floor; floor<N_FLOORS; floor++){
            if (l->panel_lights[floor] == 1){
                return floor;
            }
        }
    }
}

void elevator_controller_choose_dir(Elevator_controller* ec, Elevator* e, Lights* l){
    if(e->current_floor == 0){
        e->direction = DIRN_UP;
    }
    else if(e->current_floor == N_FLOORS-1){
        e->direction = DIRN_DOWN;
    }

    elevator_controller_update_target_floor(ec, e, l);
    
    if (ec->target_floor > e->current_floor){
        e->direction = DIRN_UP;
    } 
    else if (ec->target_floor < e->current_floor){
        e->direction = DIRN_DOWN;
    } 
    else {
        e->direction = DIRN_STOP;
    }
}
Elevator_controller Elevator_controller_initialize(){
    Elevator_controller ec = {0};
    ec.target_floor = 0;
    return ec;
}