#include "hwlib.hpp"
#include "MPU6050.hpp"
#include <array>
#include <iostream>

int main(int argc, char **argv){
	auto scl = target::pin_oc( target::pins::scl );
	auto sda = target::pin_oc( target::pins::sda );
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
	auto test = MPU6050(i2c_bus);
}
