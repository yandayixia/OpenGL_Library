#include "Timing.h"
#include <SDL/SDL.h>
namespace MyEngine{

	FpsLimiter::FpsLimiter(){}

	void FpsLimiter::Init(float maxFPS){
		SetMaxFPS(maxFPS);
	}

	void FpsLimiter::SetMaxFPS(float maxFPS){
		_maxFPS = maxFPS;
	}

	void FpsLimiter::BeginFrame(){
		_startTick = SDL_GetTicks();

	}
	void FpsLimiter::CalculatingFPS(){
		static const int NUM_SAMPLES = 100;
		//a circular buffer
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTick = (float)SDL_GetTicks();
		float currentTicks;
		currentTicks = (float)SDL_GetTicks();
		_frameTime = currentTicks - prevTick;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
		prevTick = currentTicks;

		int count;
		currentFrame++;
		if (currentFrame < NUM_SAMPLES){
			count = currentFrame;
		}
		else{
			count = NUM_SAMPLES;
		}
		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++){
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0){
			_fps = 1000.0f / frameTimeAverage;
		}
		else{
			//fake it
			_fps = 0.0f;
		}
	}

	//End will return the current FPS
	float FpsLimiter::End(){
		CalculatingFPS();

		float frameTicks = SDL_GetTicks() - _startTick;
		//Limit the FPS to the max FPS.
		if (1000.0f / _maxFPS  > frameTicks){
			//delay amount: desired amount - actual amount
			SDL_Delay((Uint32)((1000.0f / _maxFPS) - frameTicks));
		}

		return _fps;
	}
}