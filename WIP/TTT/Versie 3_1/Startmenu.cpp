#include "Startmenu.hpp"

// Starts te Start Menu.

void StartMenu::StartMenuLoop(){
	hwlib::wait_ms(500);
	displayText
	<< "\f" << "Press Button " 
	<< "\n" << "to start " << hwlib::flush;
	for(;;){
		hwlib::wait_ms(20);
		if(!continueButton.read()){
			displayText
			<< "\n" << "Button Pressed. "
			<< "\n" << "Loading game. " << hwlib::flush;
			hwlib::wait_ms(1000);
			break;
		}
	}
}