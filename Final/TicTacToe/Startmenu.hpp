#ifndef STARTMENU_HPP
#define STARTMENU_HPP

#include "hwlib.hpp"

class StartMenu{
private:
	char EndMenu;
	
	hwlib::target::pin_in continueButton = hwlib::target::pin_in( hwlib::target::pins::d13 );
	hwlib::target::pin_oc scl_OLED = hwlib::target::pin_oc( hwlib::target::pins::scl);
	hwlib::target::pin_oc sda_OLED = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda bus_OLED = hwlib::i2c_bus_bit_banged_scl_sda( scl_OLED,sda_OLED );
	hwlib::glcd_oled display = hwlib::glcd_oled( bus_OLED, 0x3c ); 
	hwlib::font_default_8x8 font = hwlib::font_default_8x8();
	hwlib::terminal_from displayText = hwlib::terminal_from( display, font );
public:
	void StartMenuLoop();
};

#endif