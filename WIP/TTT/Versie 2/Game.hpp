#ifndef GAME_HPP
#define GAME_HPP
#include "hwlib.hpp"
#include "MPU6050.hpp"

class GameControl{
private:
	
	bool XorO = true;
	
	char PlayerInput_char;
	int PlayerInput_int = 0;
	
	int Check_Counter = 0;
	int ValueCheck_hor = 0;
	int ValueCheck_ver = 0;
	int ValueCheck_dia = 0;
	bool Stop_Game = false;
	
	hwlib::target::pin_in playButton = hwlib::target::pin_in( hwlib::target::pins::d13 );
	hwlib::target::pin_in exitButton = hwlib::target::pin_in( hwlib::target::pins::d12 );
	
	hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
	hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
	MPU6050 mpu6050 = MPU6050(bus);
	
	int NumberSpotsLeft = 9;
	char board[9] = {'2','2','2','2','2','2','2','2','2'};
	
public:
	void GameLoop();
	
	void ProcessInput();
	void Update();
	void Render();
	
	void ResetValues();
	
	int Check_Horizontal();
	int Check_Vertical();
	int Check_Diagonal();
};

#endif