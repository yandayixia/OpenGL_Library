#include "MyEngine.h"

#include <SDL/SDL.h>
#include <gl/glew.h>

#include "RandomNumberGenerator.h"

namespace MyEngine{
	int Init(){
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell SDL that we want a double buffer table
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		//Initialize the RandomNumberGenerator module
		RandomNumberGenerator::InitRandomEngineGenerater();
		
		return 0;
	}
}