#include <Lights.h>
#include <elevio.h>


Lights lights_initilize(){
    Lights l;
    for (int i=0; i<4+1; i++){
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