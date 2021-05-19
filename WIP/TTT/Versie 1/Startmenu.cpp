#include "Startmenu.hpp"

void StartMenu::StartMenuLoop(){
	for(;;){
		std::cout << "test: StartMenu " << std::endl;
		std::cout << "endMenu = M " << std::endl;
		getline(std::cin, EndMenu);
		if(EndMenu == "M"){
			break;
		}
	}
}