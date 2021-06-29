#include "Statemachine.hpp"

void Statemachine::StateMachineLoop(){
	for(;;){
		switch(state){
			case STARTMENU:
				hwlib::cout << "STARTMENU: " << hwlib::endl;
				//startMenu.StartMenuLoop();
				state = GAME;
				break;
			case GAME:
				hwlib::cout << "GAME: " << hwlib::endl;
				//gameControl.GameLoop();
				state = STARTMENU;
				break;
		}
	}
}