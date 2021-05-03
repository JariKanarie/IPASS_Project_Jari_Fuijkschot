#include "Game.hpp"

void GameControl::GameLoop(){
	Render();
	for(;;){
		hwlib::wait_ms( 20 );
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
					if(!(board[i][j] == 1) && !(board[i][j] == 0)){
						if(XorO){
							board[i][j] = 1;
							NumberSpotsLeft--;
							XorO = false;
						}
						else{
							board[i][j] = 0;
							NumberSpotsLeft--;
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
	}
}

void GameControl::Render(){
	std::cout << "Test Game Render" << std::endl;
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
				std::cout << "#";
			}
		}
	}
	std::cout << std::endl;
}

void GameControl::ResetValues(){
	XorO = true;
	NumberSpotsLeft = 9;
	board = {{2, 2, 2},
			{2, 2, 2},
			{2, 2, 2}};
}
