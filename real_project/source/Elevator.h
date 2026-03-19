#pragma once
#include <unistd.h>
#include "driver/elevio.h"
#include <stdbool.h>
#include <time.h>

/**
 * @file Elevator.h
 * @brief Modul for heisen.
 *
 * @details Inneholder informasjon om heisens posisjon, retning og dørtilstand.
 */

typedef struct Lights Lights;

typedef struct Elevator{
    int current_floor;
    bool door_open;
    bool at_floor;
    MotorDirection direction;
    time_t door_open_time;
} Elevator;

void Elevator_move(Elevator* e, MotorDirection dir);
void Elevator_stop(Elevator* e);
void Elevator_open_door(Elevator* e);
void Elevator_close_door(Elevator* e);
Elevator Elevator_initialize();

/**
 * @brief Oppdaterer posisjonen fra etasjesensoren.
 *
 * @details current_floor beholdes som sist kjente etasje når heisen er mellom to etasjer.
 */
void Elevator_update_position(Elevator* e);

/**
 * @brief Håndterer stoppknappen for én iterasjon av hovedløkken.
 *
 * @details Stopper heisen, skrur på stopplyset og nullstiller bestillinger via
 * lights-strukturen. Hvis heisen står i en etasje holdes døren åpen så lenge
 * stopp er aktiv ved å oppdatere door_open_time.
 *
 * @return true hvis stoppmodus er aktiv og vanlig logikk skal hoppes over.
 */
bool Elevator_handle_stop_button(Elevator* e, Lights* lights);

/**
 * @brief Håndterer obstruksjon mens døren er åpen.
 *
 * @details Ved aktiv obstruksjon oppdateres door_open_time slik at døren ikke
 * lukkes av 3-sekunderslogikken.
 */
bool Elevator_handle_obstruction(Elevator* e);

/**
 * @brief Kjører heisen ned til nærmeste etasje hvis den starter mellom etasjer.
 */
void Elevator_initialize_pos(Elevator* e);
