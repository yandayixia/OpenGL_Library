#pragma once
#include <gl/glew.h>
namespace MyEngine{
	class FpsLimiter{
		float _maxFPS;
		unsigned int _startTick;
		
		float _fps;
		float _frameTime;
	public:
		FpsLimiter();
		void Init(float targetFPS);
		void SetMaxFPS(float targetFPS);
		void BeginFrame();
		void CalculatingFPS();
		//End will return the current FPS
		float End();
	};
}