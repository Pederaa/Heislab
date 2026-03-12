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

            if (elevator.door_open_time < 3){
                continue; //forhindrer heisen fra å kjøre mens døra er åpen
                }

            Elevator_close_door(&elevator);
        }
        // Ser om heisen skal stoppe på en etasje. Må gjøres før vi kjører videre. 
        if (elevator.at_floor && (just_arrived == false)){
            bool should_stop = elevator_controller_should_stop(elevator.current_floor, elevator.at_floor, ec);
            if (should_stop){
                Elevator_stop(&elevator);
                lights_clear_orders_at_floor(&lights, &elevator);
                Elevator_open_door(&elevator);
                just_arrived = true;
                continue;
            }
        }
        elevator_controller_change_target_floor(&ec, &elevator, &lights);

        just_arrived = false;
        // Velger retning heisen skal gå i avhengig av heisens posisjon og beestillinger.
        elevator_controller_choose_dir(&ec, &elevator);
        Elevator_move(&elevator, elevator.direction);


    }

}


int eksample_main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
