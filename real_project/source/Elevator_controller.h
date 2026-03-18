#pragma once
#include <stdbool.h>
#include "Elevator.h"
#include "Lights.h"

/**
 * @file Elevator_controller.h
 * @brief Modul for heiskontrolleren.
 */

typedef struct {
    /** -1 betyr at ingen måletasje er aktiv. */
    int target_floor;
} Elevator_controller;

/**
 * @brief Sjekker om heisen skal stoppe i etasjen den er i nå.
 */
bool elevator_controller_should_stop(int floor, bool at_floor, Elevator_controller ec);

/**
 * @brief Velger retning ut fra måletasjen.
 */
void elevator_controller_choose_dir(Elevator_controller* ec, Elevator *e);

/**
 * @brief Lager en controller uten aktiv bestilling.
 */
Elevator_controller Elevator_controller_initialize();

/**
 * @brief Velger ny måletasje ut fra aktive bestillinger.
 *
 * @details Søker først i nåværende retning, og hvis ingenting finnes der leter
 * den i motsatt retning. Hvis det ikke finnes noen bestillinger settes target til -1.
 */
void elevator_controller_change_target_floor(Elevator_controller* ec, Elevator* e, Lights* lights);

/**
 * @brief Sjekker om en etasje har minst én aktiv bestilling.
 *
 * @details Her brukes lights-strukturen også som et enkelt bestillingslager.
 */
bool elevator_controller_floor_has_order(Lights* lights, int floor);
