#include "Startmenu.hpp"

void StartMenu::StartMenuLoop(){
	hwlib::cout << "Press Button: " << hwlib::endl;
	for(;;){
		hwlib::wait_ms(20);
		if(!Button.read()){
			hwlib::cout << "Button pressed " << hwlib::endl;
			hwlib::wait_ms(1000);
			break;
		}
	}
}