#pragma once

#include <stdbool.h>

struct Elevator{
    int current_floor;
    int direction;
    bool door_open;
    bool stopPressed;
    bool at_floor;
};

// void move();
// void stop();
// void open_door();
// void floor_reached();