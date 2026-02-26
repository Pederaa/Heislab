#include <stdbool.h>
#include "Elevator.h"


void Elevator_move(Elevator* e, MotorDirection dir){
    e->direction = dir;
    elevio_motorDirection(dir);
}

void Elevator_stop(){
  elevio_motorDirection(DIRN_STOP);
}

void Elevator_open_door(Elevator* e){
    e->door_open = true;
    elevio_doorOpenLamp(1);

    sleep(3);

    elevio_doorOpenLamp(0);
    e->door_open = false;
}

bool Elevator_floor_reached(){
    int floor = elevio_floorSensor();
    if (floor != -1){
        return true;
    } else {
        return false;
    }

}