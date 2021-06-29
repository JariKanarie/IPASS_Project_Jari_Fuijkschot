#include "Game.hpp"

void GameControl::GameLoop(){
	mpu6050.WakeMeUp();
	Render(-1);
	for(;;){
		if(Stop_Game){
			ResetValues();
			display.clear(); 
			displayText 
				<< "\f" << "Player " << XorO << " wins"
				<< "\n" << "Play again? "
				<< "\n" << "Press the button" << hwlib::flush;
			break;
		}
		ProcessInput();
		if(Stop_Game == false){
			Update();
		}
		else{
			ResetValues();
			displayText 
				<< "\t0103" << "Play again? "
				<< "\t0104" << "Press the button" << hwlib::flush;
			break;
		}
	}
}

void GameControl::ProcessInput(){
	hwlib::wait_ms(300);
	PlayerInput_int = getPlayerInput();
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
					if((XorO == Check_Horizontal()) || (XorO == Check_Vertical()) || (XorO == Check_Diagonal())){
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
					displayText
					<< "\n" << "Already taken!" << hwlib::flush;
					hwlib::wait_ms(200);
				}
			}
			Counter++;
		}
	}
	else{
		displayText
		<< "\t0101" << "Its a tie "
		<< "\t0102" << "Gameboard full " << hwlib::flush;
		Stop_Game = true;
	}
}

void GameControl::Render(unsigned int tempPosition = -1){
	display.clear();
	for(unsigned int i = 0; i<sizeof(board); i++){
		if(board[i] == 48){
			number[i] = 'O';
		}
		else if(board[i] == 49){
			number[i] = 'X';
		}
		else{
			number[i] = ' ';
		}
	}
	ver_1.draw(display);
	ver_2.draw(display);
	hor_1.draw(display);
	hor_2.draw(display);
	displayText 
		<< "\t0101" << XorO
		<< "\t0502" << number[0]
		<< "\t0702" << number[1]
		<< "\t0902" << number[2]
		<< "\t0504" << number[3]
		<< "\t0704" << number[4]
		<< "\t0904" << number[5]
		<< "\t0506" << number[6]
		<< "\t0706" << number[7]
		<< "\t0906" << number[8]
		<< hwlib::flush;
	hwlib::wait_ms( 20 );
	display.flush();
}

void GameControl::ResetValues(){
	Stop_Game = false;
	XorO = true;
	NumberSpotsLeft = 9;
	for(unsigned int i = 0; i<sizeof(board); i++){
		board[i] = 50;
	}
	for(unsigned int i = 0; i<sizeof(number); i++){
		number[i] = 50;
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

int GameControl::getPlayerInput(){
	int playerPosition = 0;
	int playerInput_mpu_X = 0;
	int playerInput_mpu_Y = 0;
	for(;;){
		playerInput_mpu_X = mpu6050.getAccelX();
		playerInput_mpu_Y = mpu6050.getAccelY();
		// playerPosition 1
		if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			playerPosition = 1;
		}
		// playerPosition 2
		else if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			playerPosition = 2;
		}	
		// playerPosition 3
		else if((playerInput_mpu_X < 60000 && playerInput_mpu_X > 45000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			playerPosition = 3;
		}
		// playerPosition 4
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			playerPosition = 4;
		}
		// playerPosition 5 ( MID )
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			playerPosition = 5;
		}
		// playerPosition 6 
		else if((playerInput_mpu_X < 5000 || playerInput_mpu_X > 60000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			playerPosition = 6;
		}
		// playerPosition 7
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y > 5000 && playerInput_mpu_Y < 15000 )){
			playerPosition = 7;
		} 
		// playerPosition 8
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y < 5000 || playerInput_mpu_Y > 60000)){
			playerPosition = 8;
		}
		// playerPosition 9
		else if((playerInput_mpu_X > 5000 && playerInput_mpu_X < 15000) && (playerInput_mpu_Y < 60000 && playerInput_mpu_Y > 45000)){
			playerPosition = 9;
		}
		Render(playerPosition-1);
		hwlib::cout << "playerPosition = " << playerPosition << hwlib::endl;
		hwlib::wait_ms(20);
		if(!positionButton.read()){
			if(playerPosition != 0){
				return playerPosition;
			}
		}
		else if(!exitButton.read()){
			Stop_Game = true;
			return 0;
		}
		hwlib::wait_ms(20);
	}
}