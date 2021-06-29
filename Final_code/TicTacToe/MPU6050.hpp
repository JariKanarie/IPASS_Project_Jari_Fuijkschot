// This file contains Doxygen documentation

///file MPU6050.hpp
///\brief Class for the MPU6050 acceleration and Gyro sensor
///\details Class that uses the acceleration and Gyro componenents of the MPU6050 sensor
/// The standard address of the MPU6050 is 0x68

#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

class MPU6050{
private:
	hwlib::i2c_bus & bus;

	uint8_t dataStore[2];
	uint8_t dataStore1[1];
	uint8_t dataStore2[1];

	const uint8_t MPU_Address 	= 0x68;
	const uint8_t PWR_MGMT_1 	= 0x6B;
	const uint8_t WHO_AM_I  	= 0x75;
	const uint8_t ACCEL_XOUT_H 	= 0x3B;
	const uint8_t ACCEL_XOUT_L 	= 0x3C;
	const uint8_t ACCEL_YOUT_H 	= 0x3D;
	const uint8_t ACCEL_YOUT_L 	= 0x3E;
	const uint8_t ACCEL_ZOUT_H 	= 0x3F;
	const uint8_t ACCEL_ZOUT_L 	= 0x40;
	const uint8_t GYRO_XOUT_H  	= 0x43;
	const uint8_t GYRO_XOUT_L  	= 0x44;
	const uint8_t GYRO_YOUT_H  	= 0x45;
	const uint8_t GYRO_YOUT_L  	= 0x46;
	const uint8_t GYRO_ZOUT_H  	= 0x47;
	const uint8_t GYRO_ZOUT_L  	= 0x48;

public:
	///\brief Constructor for MPU6050
	///\detals Initializes the MPU6050
	/// The constructor requires a hwlib::i2c_bus_bit_banged_scl_sda to be initialized
	MPU6050(hwlib::i2c_bus & bus);
	
	///\brief Wakes up the MPU6050 for use of Acceleration and Gyro
	///\details This wakes up the MPU6050. This needs to be done in order to use the functions getAccel and getGyro
	void WakeMeUp();
	
	///\brief returns the device ID
	///\details returns the device ID of the MPU6050, which is standard 0x68. This can be used to test wether your connection with the MPU6050 works.
	/// Returns the ID as an INT
	int WhoAmI();
	
	///\brief returns the Acceleration X value
	///\details return the X value of the acceleration register of the MPU6050
	/// Returns the address as an INT
	int getAccelX();
	
	///\brief returns the Acceleration Y value
	///\details return the Y value of the acceleration register of the MPU6050
	/// Returns the address as an INT
	int getAccelY();
	
	///\brief returns the Acceleration Z value
	///\details return the Z value of the acceleration register of the MPU6050
	/// Returns the address as an INT
	int getAccelZ();
	
	///\brief returns the Gyro X value
	///\details return the X value of the Gyro register of the MPU6050
	/// Returns the address as an INT
	int getGyroX();
	
	///\brief returns the Gyro Y value
	///\details return the Y value of the Gyro register of the MPU6050
	/// Returns the address as an INT
	int getGyroY();
	
	///\brief returns the Gyro Z value
	///\details return the Z value of the Gyro register of the MPU6050
	/// Returns the address as an INT
	int getGyroZ();
};

#endif