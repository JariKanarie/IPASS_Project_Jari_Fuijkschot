#include "Statemachine.hpp"

// Changes in between 2 states to make the game playable

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
				hwlib::wait_ms(300);
				state = STARTMENU;
				break;
		}
	}
}
