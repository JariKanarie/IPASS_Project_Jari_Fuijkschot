#ifndef GAME_HPP
#define GAME_HPP
#include "hwlib.hpp"
#include "MPU6050.hpp"

class GameControl{
private:
	
	bool XorO = true;
	
	char PlayerInput_char;
	int PlayerInput_int = 0;
	
	int playerPosition = 0;
	int previousPlayerPosition = 0;
	int playerInput_mpu_X = 0;
	int playerInput_mpu_Y = 0;
	
	int Check_Counter = 0;
	bool Stop_Game = false;
	
	hwlib::target::pin_in positionButton = hwlib::target::pin_in( hwlib::target::pins::d13 );
	hwlib::target::pin_in exitButton = hwlib::target::pin_in( hwlib::target::pins::d12 );
	
	hwlib::target::pin_oc scl_mpu = hwlib::target::pin_oc( hwlib::target::pins::d3 );
	hwlib::target::pin_oc sda_mpu = hwlib::target::pin_oc( hwlib::target::pins::d2 );
	hwlib::i2c_bus_bit_banged_scl_sda bus_MPU = hwlib::i2c_bus_bit_banged_scl_sda( scl_mpu,sda_mpu );
	MPU6050 mpu6050 = MPU6050(bus_MPU);
	
	hwlib::target::pin_oc scl_OLED = hwlib::target::pin_oc( hwlib::target::pins::scl);
	hwlib::target::pin_oc sda_OLED = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda bus_OLED = hwlib::i2c_bus_bit_banged_scl_sda( scl_OLED,sda_OLED );
	hwlib::glcd_oled display = hwlib::glcd_oled( bus_OLED, 0x3c ); 
	hwlib::font_default_8x8 font = hwlib::font_default_8x8();
	hwlib::terminal_from displayText = hwlib::terminal_from( display, font );
	
	hwlib::line ver_1 = hwlib::line(hwlib::xy(50, 10), hwlib::xy(50, 60));
	hwlib::line ver_2 = hwlib::line(hwlib::xy(68, 10), hwlib::xy(68, 60));
	hwlib::line hor_1 = hwlib::line(hwlib::xy(35, 25), hwlib::xy(85, 25));
	hwlib::line hor_2 = hwlib::line(hwlib::xy(35, 45), hwlib::xy(85, 45));
	
	char number[9] = {'1','2','2','5','2','2','2','2','9'};	
	
	int NumberSpotsLeft = 9;
	char board[9] = {'2','2','2','2','2','2','2','2','2'};
	
public:
	void GameLoop();

	void Update();
	void Render(unsigned int tempPosition);
	
	void ResetValues();
	
	int Check_Horizontal();
	int Check_Vertical();
	int Check_Diagonal();
	
	int getPlayerInput();
};

#endif