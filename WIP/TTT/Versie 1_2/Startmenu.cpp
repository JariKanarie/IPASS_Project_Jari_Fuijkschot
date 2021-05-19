#include "Startmenu.hpp"

void StartMenu::StartMenuLoop(){
	for(;;){
		std::cout << "endMenu = M " << std::endl;
		getline(std::cin, EndMenu);
		if(EndMenu == "M" || EndMenu == "m"){
			break;
		}
	}
}