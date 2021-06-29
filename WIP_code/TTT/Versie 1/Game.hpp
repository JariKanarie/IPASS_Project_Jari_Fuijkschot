#ifndef GAME_HPP
#define GAME_HPP

#include "hwlib.hpp"

#include <iostream>

class GameControl{
private:
	
	bool XorO; // true = X, false = O
	
	std::string PlayerInput_string;
	int PlayerInput_int;
	
	int NumberSpotsLeft;
	std::vector<std::vector<int>> board = {{2, 2, 2},
										{2, 2, 2},
										{2, 2, 2}};
public:
	void GameLoop();
	
	void ProcessInput();
	void Update();
	void Render();
	void ResetValues();
};

#endif