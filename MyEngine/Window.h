#pragma once
#include <SDL/SDL.h>
#include <gl/glew.h>
#include <string>

//  1
// 10
//100

namespace MyEngine{
	//Each flag sets a bit-wise tag. The i-th flag takes the the i-th rightmost bit in the unsigned 32-bit int 
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x1, BORDERLESS = 0x4 };

	//Represent each window to be opened.
	class Window{
		SDL_Window * _sdlWindow;
		int _screenWidth, _screenHeight;

	public:
		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		
		//Getter functions for width/height
		int GetScreenWidth();
		int GetScreenHeight();

		//Called to swap the window buffer with the backup to draw out what's on screen. Simply a wrapper of 
		//the openGL function to be called by the Draw function of the main program.
		void SwapBuffer();

		Window();
		~Window();
	};
}