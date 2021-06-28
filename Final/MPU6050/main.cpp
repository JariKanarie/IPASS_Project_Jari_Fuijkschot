#include "hwlib.hpp"
#include "MPU6050.hpp"

int main(){
	hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
	hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
	hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
	MPU6050 mpu6050 = MPU6050(bus);
	
	mpu6050.WakeMeUp();
	
	hwlib::cout << mpu6050.WhoAmI() << hwlib::endl;
	
	
	if(mpu6050.WhoAmI() == 0x68 ){
		hwlib::cout << "Succes " << hwlib::endl;
	}
	else{
		hwlib::cout << "fail" << hwlib::endl;
	}
	hwlib::wait_ms(100);
	for(;;){
		hwlib::cout << "Accel X = " << mpu6050.getAccelX() << hwlib::endl;
		hwlib::cout << "Accel Y = " << mpu6050.getAccelY() << hwlib::endl;
	}
}	
