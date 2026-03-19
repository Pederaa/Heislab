#pragma once
#include "driver/elevio.h"
#include "Elevator.h"

typedef struct Elevator  Elevator;

/** @file Lights.h */

typedef struct Lights{
    int floor_lights[N_FLOORS];
    int panel_lights[N_FLOORS];
    int opp_lights[N_FLOORS];
    int ned_lights[N_FLOORS];
} Lights;

/**
 * @brief Nullstiller alle lagrede lys- og bestillingstilstander.
 */
void lights_initilize(Lights *lights);

/**
 * @brief Oppdaterer intern tilstand for etasjelyset.
 */
void lights_setfloorIndicator(Lights *lights, int floor, int value);

/**
 * @brief Oppdaterer intern tilstand for opp- eller ned-bestilling.
 */
void lights_setOrderlIght(Lights *lights, int floor, MotorDirection dir, int value);

/**
 * @brief Oppdaterer intern tilstand for kabinbestilling.
 */
void lights_setPanellIght(Lights *lights, int floor, int value);

/**
 * @brief Oppdaterer hardware-lys og lagrer nye bestillinger.
 *
 * @details lights brukes både til å styre lysene og til å huske hvilke bestillinger
 * som er aktive akkurat nå.
 */
void lights_updateLights(Lights *lights, Elevator *e);

/**
 * @brief Fjerner alle lagrede bestillinger i heisens nåværende etasje.
 *
 * @details Brukes når en etasje er betjent, så lysene i den etasjen slukkes igjen.
 */
void lights_clear_orders_at_floor(Lights* lights, Elevator* e);
