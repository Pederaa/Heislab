#include "Lights.h"
#include "Elevator.h"
#include "driver/elevio.h"

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

void lights_setPanellIght(Lights *lights, int floor, int value){
    (*lights).panel_lights[floor] = value;
}

void lights_updateLights(Lights *lights, Elevator *e){
    // Oppdaterer etasjelampene
    elevio_floorIndicator(e->current_floor);

    // Oppdaterer beestilingsknappene
    for (int floor=0; floor<N_FLOORS; floor++){
        // Nedknappene
        ButtonType btn = BUTTON_HALL_DOWN;
        bool isButtonPressed = elevio_callButton(floor, btn);
        if (isButtonPressed){
            lights_setOrderlIght(lights, floor, DIRN_DOWN, 1);
        }
        elevio_buttonLamp(floor, btn, lights->ned_lights[floor]);

        // Oppknappene
        btn = BUTTON_HALL_UP;
        isButtonPressed = elevio_callButton(floor, btn);
        if (isButtonPressed){
            lights_setOrderlIght(lights, floor, DIRN_UP, 1);
        }
        elevio_buttonLamp(floor, btn, lights->opp_lights[floor]);

        // Heispanelknappene
        btn = BUTTON_CAB;
        isButtonPressed = elevio_callButton(floor, btn);
        if (isButtonPressed){
            lights_setPanellIght(lights, floor, 1);
        }
        elevio_buttonLamp(floor, btn, lights->panel_lights[floor]);
    }
}