#include "MPU6050.hpp"

MPU6050::MPU6050(hwlib::i2c_bus & bus):
	bus(bus)
	{}
	
void MPU6050::WakeMeUp(){
	auto trans = bus.write(MPU_Address);
	trans.write(0x6B);
	trans.write(0x00);
}

int MPU6050::WhoAmI(){
	bus.write(MPU_Address).write(WHO_AM_I);
	bus.read(MPU_Address).read(dataStore, 2);
	int data = dataStore[0]; // returns 0x68 ( int 104 )
	return data;
}

int MPU6050::getAccelX(){
	bus.write(MPU_Address).write(ACCEL_XOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(ACCEL_XOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8) | dataStore2[0];
	return data;
}

int MPU6050::getAccelY(){
	bus.write(MPU_Address).write(ACCEL_YOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(ACCEL_YOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8 ) | dataStore2[0];
	return data;
}

int MPU6050::getAccelZ(){
	bus.write(MPU_Address).write(ACCEL_ZOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(ACCEL_ZOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8) | dataStore2[0];
	return data;
}

int MPU6050::getGyroX(){
	bus.write(MPU_Address).write(GYRO_XOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(GYRO_XOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8 ) | dataStore2[0];
	return data;
}

int MPU6050::getGyroY(){
	bus.write(MPU_Address).write(GYRO_YOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(GYRO_YOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8 ) | dataStore2[0];
	return data;
}

int MPU6050::getGyroZ(){
	bus.write(MPU_Address).write(GYRO_ZOUT_H);
	bus.read(MPU_Address).read(dataStore1, 1);
	bus.write(MPU_Address).write(GYRO_ZOUT_L);
	bus.read(MPU_Address).read(dataStore2, 1);
	int data = (dataStore1[0] << 8 ) | dataStore2[0];
	return data;
}