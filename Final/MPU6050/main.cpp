#include "hwlib.hpp"
#include "MPU6050.hpp"
#include <array>

int main(){
	hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
	hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
	MPU6050 mpu6050 = MPU6050(bus);
	
	hwlib::target::pin_in positionButton = hwlib::target::pin_in( hwlib::target::pins::d13 );
	
	mpu6050.WakeMeUp();
	
	hwlib::cout << mpu6050.WhoAmI() << hwlib::endl;
	
	
	if(mpu6050.WhoAmI() == 0x68 ){
		hwlib::cout << "Succes " << hwlib::endl;
	}
	else{
		hwlib::cout << "fail" << hwlib::endl;
	}
	hwlib::wait_ms(100);
	int Positie = 0;
	int playerInput_mpu_X = 0;
	int playerInput_mpu_Y = 0;
	for(;;){
		playerInput_mpu_X = mpu6050.getAccelX();
		playerInput_mpu_Y = mpu6050.getAccelY();
		// Positie 1
		hwlib::cout << "Accel X = " << mpu6050.getAccelX() << hwlib::endl;
		hwlib::cout << "Accel Y = " << mpu6050.getAccelY() << hwlib::endl;
		if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			Positie = 1;
		}
		// Positie 2
		else if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			Positie = 2;
		}	
		// Positie 3
		else if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			Positie = 3;
		}
		// Positie 4
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			Positie = 4;
		}
		// Positie 5 ( MID )
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			Positie = 5;
		}
		// Positie 6 
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			Positie = 6;
		}
		// Positie 7
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			Positie = 7;
		} 
		// Positie 8
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			Positie = 8;
		}
		// Positie 9
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			Positie = 9;
		}
		hwlib::cout << "POSITIE = " << Positie << hwlib::endl;
		hwlib::wait_ms(300);
		if(!positionButton.read()){
			hwlib::cout << "END loop with position = " << Positie << hwlib::endl;
			break;
		}
	}
}
