#ifndef STARTMENU_HPP
#define STARTMENU_HPP

#include "hwlib.hpp"

class StartMenu{
private:
	char EndMenu;
	
	hwlib::target::pin_in Button = hwlib::target::pin_in( hwlib::target::pins::d13 );
public:
	void StartMenuLoop();
};

#endif