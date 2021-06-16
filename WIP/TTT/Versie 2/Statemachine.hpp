#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "hwlib.hpp"
#include "Startmenu.hpp"
#include "Game.hpp"

class Statemachine {
private:
	enum state_t {STARTMENU, GAME};
	state_t state = STARTMENU;
	
	StartMenu startMenu;
	GameControl Game;
public:
	void StateMachineLoop();
};

#endif