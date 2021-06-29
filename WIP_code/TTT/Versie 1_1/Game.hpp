#ifndef GAME_HPP
#define GAME_HPP

#include "hwlib.hpp"

#include <iostream>

class GameControl{
private:
	
	bool XorO = true; // true = X, false = O
	
	std::string PlayerInput_string;
	int PlayerInput_int;
	
	int Check_Counter;
	int ValueCheck_hor = 0;
	int ValueCheck_ver = 0;
	int ValueCheck_dia = 0;
	bool Stop_Game = false;
	
	int NumberSpotsLeft = 9;
	std::vector<std::vector<int>> board = {{2, 2, 2},
										{2, 2, 2},
										{2, 2, 2}};
public:
	void GameLoop();
	
	void ProcessInput();
	void Update();
	void Render();
	
	void ResetValues();
	
	int Check_Horizontal();
	int Check_Vertical();
	int Check_Diagonal();
};

#endif