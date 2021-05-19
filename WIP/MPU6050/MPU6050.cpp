#include "MPU6050.hpp"

MPU6050::MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus):
	i2c_bus(i2c_bus)
	{}
	
void MPU6050::WakeMeUp(){
	i2c_bus.write(MPU_Address, PWR_MGMT_1, 2);
}

int MPU6050::WhoAmI(){
	i2c_bus.write(MPU_Address, WHO_AM_I, 2);
	i2c_bus.read(MPU_Address, dataStore);
	int data = dataStore;
	return data;
}