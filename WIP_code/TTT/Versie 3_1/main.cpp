#include "Statemachine.hpp"

int main(){
	hwlib::wait_ms(2000);
	Statemachine state = Statemachine();
	state.StateMachineLoop();
}
