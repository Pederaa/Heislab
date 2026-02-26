#pragma once
#include <unistd.h>

typedef struct{
    int current_floor;
    int direction;
    bool door_open;
    bool stopPressed;
    bool at_floor;
} Elevator;

// void move();
// void stop();
void Elevator_open_door();
// void floor_reached();