#include <stdbool.h>
#include "Elevator.h"
#include "driver/elevio.h"
#include "Lights.h"


void Elevator_move(Elevator* e, MotorDirection dir){
    e->direction = dir;
    elevio_motorDirection(dir);
}

void Elevator_stop(Elevator* e){
    e->direction = DIRN_STOP;
    elevio_motorDirection(DIRN_STOP);
}

void Elevator_open_door(Elevator* e){
    e->door_open = true;
    e->door_open_time = time(NULL);
    elevio_doorOpenLamp(1);
}

void Elevator_close_door(Elevator* e){
    e->door_open = false;
    elevio_doorOpenLamp(0);
}

Elevator Elevator_initialize(){
    Elevator e = {0};
    int sensor_value = elevio_floorSensor();
        if (sensor_value >= 0) {
            e.current_floor = sensor_value;
            e.at_floor = true;
        } else {
            e.current_floor = sensor_value;
            e.at_floor = false;
            }
    e.direction = DIRN_STOP;
    e.door_open = false;
    e.door_open_time = time(NULL);
    return e;
}

void Elevator_update_position(Elevator* e){
    int sensor_value = elevio_floorSensor();
        if (sensor_value >= 0) {
            e->current_floor = sensor_value;
            e->at_floor = true;
        } else {
            e->at_floor = false;
            }
}

bool Elevator_handle_stop_button(Elevator* e, Lights* lights){
    //stopp trykkes ned, continue forhindrer nye bestillinger mens dette skjer.
    Elevator_update_position(e);
    if(elevio_stopButton()){
        Elevator_stop(e);
        elevio_stopLamp(1);

        lights_initilize(lights);

         //dør er åpen
        if (e->door_open){
            e->door_open_time = time(NULL);
        }
        if (e->at_floor){
            Elevator_open_door(e);
            e->door_open_time = time(NULL);
        }
        return true;
    }
    elevio_stopLamp(0); //skrur av stopplyset, og vi returnerer false for å ikke restarte while loopen i main

    return false;

}

bool Elevator_handle_obstruction(Elevator* e){
    if(elevio_obstruction() && e->door_open){ //siste sjekk er ikke nødvendig, mest for robusthet
        e->door_open_time = time(NULL);
        return true;
    }
    return false;
}

void Elevator_initialize_pos(Elevator* e){
    if (elevio_floorSensor() == -1){
        Elevator_move(e, DIRN_DOWN);
        while (elevio_floorSensor() == -1){}
        Elevator_stop(e);
        Elevator_update_position(e);
        }
    }
