#include "Statemachine.hpp"

void Statemachine::StateMachineLoop(){
	for(;;){
		hwlib::wait_ms(20);
		switch(state){
			case STARTMENU:
				startMenu.StartMenuLoop();
				state = GAME;
				break;
			case GAME:
				gameControl.GameLoop();
				state = STARTMENU;
				break;
		}
	}
}
