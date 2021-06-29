#include "Statemachine.hpp"

void Statemachine::StateMachineLoop(){
	std::cout << "Test: StateMachineLoop" << std::endl;
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
