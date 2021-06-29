#include "Game.hpp"

// Main loop voor the game
// Checks if the game needs to stop or starts diffrent functions
// It wakes up the mpu6050 before the game starts.
// if the mpu6050 loses power during the game the device will got to sleep and the game wont work anymore. Restarting the game will fix it.

void GameControl::GameLoop(){
	mpu6050.WakeMeUp();
	Render(-1);
	for(;;){
		if(Stop_Game){
			display.clear(); 
			displayText 
				<< "\f" << "Player " << XorO << " wins" << hwlib::flush;
			hwlib::wait_ms(3000);
			ResetValues();
			break;
		}
		PlayerInput_int = getPlayerInput();
		if(Stop_Game == false){
			Update();
		}
		else{
			ResetValues();
			display.clear();
			displayText 
				<< "\f" << "Play again? "
				<< "\n" << "Press the button" << hwlib::flush;
			break;
		}
	}
}

// updates the board and checkes if there is a winner, a tie or the game needs to continue.
// update function also changes the values of board[9] and it changes the bool XorO

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
					hwlib::wait_ms(100);
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

// Renders the game on the OLED
// If tempPosition is given. This wil be displayed on the the OLED as the currenct position for playerInput
// it will display the bool XorO on the top left of the OLED to display which players turn it is.

void GameControl::Render(unsigned int tempPosition){
	display.clear();
	for(unsigned int i = 0; i<sizeof(board); i++){
		if(i == tempPosition){
			number[i] = i+49;
		}
		else if(board[i] == 48){
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
	hwlib::wait_ms( 50 );
	display.flush();
}

// Resets all values. This is needed to make the game replayable
// For board[9] and number[9] it swaps all numbers to 50 which is ascii number for '2'

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

// Checks if there is a winner on the horizontal lines

int GameControl::Check_Horizontal(){
	if(XorO == (board[0]-48)){
		if((board[0] == board[1]) && (board[1] == board[2])){
			return XorO;
		}
	}
	else if(XorO == (board[3]-48)){
		if((board[3] == board[4]) && (board[4] == board[5])){
			return XorO;
		}
	}
	else if(XorO == (board[6]-48)){
		if((board[6] == board[7]) && (board[7] == board[8])){
			return XorO;
		}
	}
	return 2;
}

// Checks if there is a winner on the Vertical lines

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

// Checks if there is a winner on the Diagonal lines

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

// Gets the playerInput from the MPU6050
// It wil also do a render with a positive value as parameter to render current position to show on the OLED
// It wil not render if the current Position is == previousPlayerPosition to make it run smoother

int GameControl::getPlayerInput(){
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
		if(previousPlayerPosition != playerPosition){
			Render(playerPosition-1);
			previousPlayerPosition = playerPosition;
		}
		if(!positionButton.read()){
			hwlib::wait_ms(500);
			return playerPosition;
		}
		else if(!exitButton.read()){
			Stop_Game = true;
			return 0;
		}
	}
}