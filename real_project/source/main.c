#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <stdbool.h>
#include "Elevator_controller.h"
#include "Elevator.h"
#include "Lights.h"

int main(){
    elevio_init();
    Elevator elevator = Elevator_initialize();
    Elevator_controller ec = Elevator_controller_initialize();
    Elevator_initialize_pos(&elevator);
    Lights lights = {0};
    bool just_arrived = false;


    while(true){
        
        lights_updateLights(&lights, &elevator);

        
        if (Elevator_handle_stop_button(&elevator, &lights)){    //Håndterer stopplogikken
            continue;
        }


        Elevator_update_position(&elevator); //oppdaterer etasje jevnlig
            
        //kontinuerlig sjekk om dør er åpen
        if (elevator.door_open) {

            //sjekker om det er en obstruksjon mens heisdøra er åpen
            if (Elevator_handle_obstruction(&elevator)){
                continue;
            }

            if (time(NULL) - elevator.door_open_time < 3){
                continue; //forhindrer heisen fra å kjøre mens døra er åpen
                }

            Elevator_close_door(&elevator);
        }
        // Ser om heisen skal stoppe på en etasje. Må gjøres før vi kjører videre. 
        if (elevator.at_floor && elevator_controller_floor_has_order(&lights, elevator.current_floor)){ {
            
            bool should_stop = elevator_controller_should_stop(elevator.current_floor, elevator.at_floor, ec);
            
            if (should_stop){
                Elevator_stop(&elevator);
                lights_clear_orders_at_floor(&lights, &elevator);
                Elevator_open_door(&elevator);
                ec.target_floor = -1;
                continue;
            }
        }
        if (ec.target_floor == -1) {
            elevator_controller_change_target_floor(&ec, &elevator, &lights);
        }

        // Velger retning heisen skal gå i avhengig av heisens posisjon og beestillinger.
        elevator_controller_choose_dir(&ec, &elevator);
        Elevator_move(&elevator, elevator.direction);


    }
    }
}