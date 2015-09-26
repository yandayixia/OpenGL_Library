#include "Window.h"

#include "FatalErrors.h"

#include <string>

namespace MyEngine{
	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
		//Bitwise adds the proper bits into one flags variable.
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE){
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN){
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (currentFlags & BORDERLESS){
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//create a dynamic window 
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		//error checking
		if (_sdlWindow == nullptr){
			FatalError("SDL Window could not be created!!!");
		}

		//create a GLContext based on the window created
		SDL_GLContext tempglContex = SDL_GL_CreateContext(_sdlWindow);
		//error checking
		if (tempglContex == nullptr){
			FatalError("SDL_GL_CONTEXT could not be created!!!");
		}

		//Initialize the glew library
		GLenum error = glewInit();
		if (error != GLEW_OK){
			FatalError("Initialize glew init failure.");
		}

		//Set up the backgroud color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//blue

		//set up VSYNC
		SDL_GL_SetSwapInterval(0);

		//enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer(){
		SDL_GL_SwapWindow(_sdlWindow);
	}
	int Window::GetScreenWidth(){
		return _screenWidth;
	}
	int Window::GetScreenHeight(){
		return _screenHeight;
	}

	//empty constructor &  destructor. 
	Window::Window(){}
	Window::~Window(){}
}