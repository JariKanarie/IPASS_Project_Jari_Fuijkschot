#include "Statemachine.hpp"

int main(){
   Statemachine state = Statemachine();
   hwlib::cout << "MAIN: " << hwlib::endl;
   state.StateMachineLoop();
}