#include "FatalErrors.h"
#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>

namespace MyEngine{
	void FatalError(std::string errormessage){
		std::cout << errormessage << std::endl;
		std::cout << "Error Spotted!!! Enter any key to quit..." << std::endl;
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);
	}
}