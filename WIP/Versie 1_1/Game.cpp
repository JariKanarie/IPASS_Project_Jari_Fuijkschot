#include "Game.hpp"

void GameControl::GameLoop(){
	Render();
	for(;;){
		hwlib::wait_ms( 20 );
		if(Stop_Game){
			if(XorO){
				std::cout << "Player X wins " << std::endl;
			}
			else{
				std::cout << "Player O wins " << std::endl;
			}
			ResetValues();
			std::cout << "Play Again? " << std::endl;
			break;
		}
		ProcessInput();
		if(!(PlayerInput_string == "E")){
			Update();
		}
		else{
			ResetValues();
			std::cout << "Play Again? " << std::endl;
			break;
		}
		Render();
	}
}

void GameControl::ProcessInput(){
	for(;;){
		if(XorO){
			std::cout << "Place X on location: " << std::endl;
			getline(std::cin, PlayerInput_string);
		}
		else{
			std::cout << "Location for O: " << std::endl;
			getline(std::cin, PlayerInput_string);
			
		}
		if(PlayerInput_string == "E"){
			break;
		}
		int PlayerInput_int = stoi(PlayerInput_string);
		if(PlayerInput_int >= 1 && PlayerInput_int <= 9){
			break;
		}
	}
}

void GameControl::Update(){
	int Counter = 1;
	int PlayerInput_int = stoi(PlayerInput_string);
	if(!(NumberSpotsLeft == 0)){
		for(unsigned int i = 0; i<board.size(); i++){
			for(unsigned int j = 0; j<board[i].size(); j++){
				if(Counter == PlayerInput_int){
					if(board[i][j] == 2){
						if(XorO){
							board[i][j] = 1;
							NumberSpotsLeft--;
						}
						else{
							board[i][j] = 0;
							NumberSpotsLeft--;
						}
						ValueCheck_hor = Check_Horizontal();
						ValueCheck_ver = Check_Vertical();
						std::cout << "VALUECHECK: " << ValueCheck_hor << std::endl;
						if(XorO == ValueCheck_hor || XorO == ValueCheck_ver) {
							Stop_Game = true;
							break;
						}
						if(XorO){
							XorO = false;
						}
						else{
							XorO = true;
						}
					}
					else{
						std::cout << "Wrong input: " << Counter << " is already taken " << std::endl;
					}
				}
				Counter++;
			}
		}
	}
	else{
		std::cout << "GameBoard is full " << std::endl;
		Stop_Game = true;
	}
}

void GameControl::Render(){
	for(unsigned int i = 0; i<board.size(); i++){
		std::cout << std::endl;
		for(unsigned int j = 0; j<board[i].size(); j++){
			if(board[i][j] == 0){
				std::cout << "O";
			}
			else if(board[i][j] == 1){
				std::cout << "X";
			}
			else{
				std::cout << "-";
			}
		}
	}
	std::cout << std::endl;
}

void GameControl::ResetValues(){
	ValueCheck_hor = 0;
	ValueCheck_ver = 0;
	ValueCheck_dia = 0;
	Stop_Game = false;
	XorO = true;
	NumberSpotsLeft = 9;
	board = {{2, 2, 2},
			{2, 2, 2},
			{2, 2, 2}};
}

int GameControl::Check_Horizontal(){
	for(unsigned int i = 0; i<board.size(); i++){
		Check_Counter = 0;
		for(unsigned int j = 0; j<board[i].size(); j++){
			if(XorO == board[i][j]){
				Check_Counter++;
				if(Check_Counter == 3){
					return XorO;
				}
			}
			else{
				Check_Counter = 0;
				break;
			}
		}
	}
	return 2;
}

int GameControl::Check_Vertical(){
	for(unsigned int i = 0; i<board.size(); i++){
		Check_Counter = 0;
		for(unsigned int j = 0; j<board[i].size(); j++){
			if(XorO == board[j][i]){
				Check_Counter++;
				if(Check_Counter == 3){
					return XorO;
				}
			}
			else{
				Check_Counter = 0;
				break;
			}
		}
	}
	return 2;
}

int GameControl::Check_Diagonal(){
	return 2;
}