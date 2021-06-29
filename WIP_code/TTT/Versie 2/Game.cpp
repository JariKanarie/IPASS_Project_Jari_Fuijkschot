#include "Game.hpp"

void GameControl::GameLoop(){
	mpu6050.WakeMeUp();
	Render();
	hwlib::cout << "Device ID: " << mpu6050.WhoAmI() << hwlib::endl;
	for(;;){
		if(Stop_Game){
			if(XorO){
				hwlib::cout << "Player X wins " << hwlib::endl;
			}
			else{
				hwlib::cout << "Player O wins " << hwlib::endl;
			}
			ResetValues();
			hwlib::cout << "Play Again? " << hwlib::endl;
			break;
		}
		ProcessInput();
		if(Stop_Game == false){
			Update();
		}
		else{
			ResetValues();
			hwlib::cout << "Play Again? " << hwlib::endl;
			break;
		}
		Render();
	}
}

void GameControl::ProcessInput(){
	if(XorO){
		hwlib::cout << "Place X on location: " << hwlib::endl;
	}
	else{
		hwlib::cout << "Location for O: " << hwlib::endl;
	}
	for(;;){
		if(!exitButton.read()){
			Stop_Game = true;
			break;
		}
		else if(!playButton.read()){
			hwlib::cout << "Geef getal: " << hwlib::endl;
			hwlib::cin >> PlayerInput_char;
			PlayerInput_int = PlayerInput_char;
			PlayerInput_int -= 48;
			if(PlayerInput_int >= 1 && PlayerInput_int <= 9){
				hwlib::cout << PlayerInput_char << hwlib::endl;
				break;
			}
		}
	}
}

void GameControl::Update(){
	int Counter = 1;
	if(!(NumberSpotsLeft == 0)){
		for(unsigned int i = 0; i<sizeof(board); i++){
			if(Counter == PlayerInput_int){
				if(board[i] == 50){
					if(XorO){
						board[i] = 49;
						NumberSpotsLeft--;
					}
					else{
						board[i] = 48;
						NumberSpotsLeft--;
					}
					ValueCheck_hor = Check_Horizontal();
					ValueCheck_ver = Check_Vertical();
					ValueCheck_dia = Check_Diagonal();
					if(XorO == ValueCheck_hor || XorO == ValueCheck_ver || XorO == ValueCheck_dia) {
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
					hwlib::cout << "Wrong input: " << Counter << " is already taken " << hwlib::endl;
				}
			}
			Counter++;
		}
	}
	else{
		hwlib::cout << "GameBoard is full " << hwlib::endl;
		Stop_Game = true;
	}
}

void GameControl::Render(){
	int end_counter = 0;
	for(unsigned int i = 0; i<sizeof(board); i++){
		if(board[i] == 48){
			hwlib::cout << "O";
		}
		else if(board[i] == 49){
			hwlib::cout << "X";
		}
		else{
			hwlib::cout << "-";
		}
		end_counter++;
		if(end_counter == 3){
			hwlib::cout << hwlib::endl;
			end_counter = 0;
		}
	}
}

void GameControl::ResetValues(){
	ValueCheck_hor = 0;
	ValueCheck_ver = 0;
	ValueCheck_dia = 0;
	Stop_Game = false;
	XorO = true;
	NumberSpotsLeft = 9;
	for(unsigned i = 0; i<sizeof(board); i++){
		board[i] = 50;
	}
}

int GameControl::Check_Horizontal(){
	int Check_Counter = 0;
	int Check_row = 0;
	PlayerInput_int -= 48;
	for(unsigned int i = 0; i<sizeof(board); i++){
		if(XorO == (board[i]-48)){
			Check_Counter++;
			if(Check_Counter == 3){
				return XorO;
			}
		}
		else{
			Check_Counter = 0;
		}
		if(Check_row == 2){
			Check_Counter = 0;
			Check_row = 0;
		}
		Check_row++;
	}
	return 2;
}

int GameControl::Check_Vertical(){
	if(XorO == (board[0]-48)){
		if((board[0] == board[3]) && (board[3] == board[6])){
			return XorO;
		}
	}
	else if(XorO == (board[1]-48)){
		if((board[1] == board[4]) && (board[4] == board[7])){
			return XorO;
		}
	}
	else if(XorO == (board[2]-48)){
		if((board[2] == board[5]) && (board[5] == board[8])){
			return XorO;
		}
	}
	return 2;
}

int GameControl::Check_Diagonal(){
	if(XorO == (board[0]-48)){
		if((board[0] == board[4]) && (board[4] == board[8])){
			return XorO;
		}
	}
	if(XorO == (board[2]-48)){
		if((board[2] == board[4]) && (board[4] == board[6])){
			return XorO;
		}
	}
	return 2;
}