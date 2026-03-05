#include <stdbool.h>
#include "Elevator.h"
#include "driver/elevio.h"



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

bool Elevator_floor_reached(){
    int floor = elevio_floorSensor();
    if (floor != -1){
        return true;
    } else {
        return false;
    }

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