#pragma once

#include <ctime>
#include <random>

namespace MyEngine{
	class RandomNumberGenerator
	{
		static std::default_random_engine* _myEngine;
		static std::uniform_int_distribution<int>* _intRange;
		static std::uniform_real_distribution<float>* _floatRange;
	public:
		static void InitRandomEngineGenerater();
		static void SetFloatRange(float min, float max);
		static void SetIntRange(int min, int max);
		static int GetIntValue();
		static float GetFloatValue();
		static void FreeRandomEngineGenerater();
	};
}