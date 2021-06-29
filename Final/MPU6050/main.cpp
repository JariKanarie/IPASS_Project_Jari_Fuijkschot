#include "hwlib.hpp"
#include "MPU6050.hpp"

int main(){
	hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::d3 );
	hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::d2 );
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
	hwlib::wait_ms(2000);
	for(;;){
		hwlib::wait_ms(200);
		hwlib::cout << "Accel X = " << mpu6050.getAccelX() << hwlib::endl;		
//		hwlib::cout << "Accel Y = " << mpu6050.getAccelY() << hwlib::endl;
//		hwlib::cout << "Accel Z = " << mpu6050.getAccelZ() << hwlib::endl;
//		hwlib::cout << "Gyro X = " << mpu6050.getGyroX() << hwlib::endl;
//		hwlib::cout << "Gyro Y = " << mpu6050.getGyroY() << hwlib::endl;
//		hwlib::cout << "Gyro Z = " << mpu6050.getGyroZ() << hwlib::endl;
	}
}
