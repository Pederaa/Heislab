#include <Lights.h>
#include <Elevator.h>
#include <elevio.h>

Lights lights_initilize(){
    Lights l;
    for (int i=0; i<N_FLOORS; i++){
        l.floor_lights[i] = 0;
        l.panel_lights[i] = 0;  
        l.opp_lights[i] = 0;
        l.ned_lights[i] = 0;
    }

    return l;
};

void lights_setfloorIndicator(Lights *lights, int floor, int value){
    (*lights).floor_lights[floor] = value;
}

void lights_setOrderlIght(Lights *lights, int floor, MotorDirection dir, int value){
    if (dir == DIRN_UP){
        (*lights).opp_lights[floor] = value;
    }
    else if (dir == DIRN_DOWN){
        (*lights).ned_lights[floor] = value;
    }
}

void lights_updateLights(Lights *lights, Elevator *e){
    elevio_floorIndicator(e->current_floor);

    for (int floor=0; floor<N_FLOORS; floor++){
        for (int button=0; button<N_BUTTONS; button++){
            if (elevio_callButton(floor, button)){
                MotorDirection dir;
                if (button = 0){
                    dir = DIRN_DOWN;
                } else {
                    dir = DIRN_UP;
                }
                lights_setOrderlIght(lights, floor, dir, 1);
            }
        }
    }
}