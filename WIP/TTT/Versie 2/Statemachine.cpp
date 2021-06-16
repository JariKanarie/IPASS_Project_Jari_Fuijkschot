#include "Statemachine.hpp"

void Statemachine::StateMachineLoop(){
	for(;;){
		switch(state){
			case STARTMENU:
				startMenu.StartMenuLoop();
				state = GAME;
				hwlib::wait_ms(100);
				break;
			case GAME:
				Game.GameLoop();
				hwlib::wait_ms(100);
				state = STARTMENU;
				break;
		}
	}
}
