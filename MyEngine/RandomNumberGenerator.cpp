#include "RandomNumberGenerator.h"

#include <ctime>
#include <random>

namespace MyEngine{

	std::default_random_engine* RandomNumberGenerator::_myEngine = nullptr;
	std::uniform_int_distribution<int>* RandomNumberGenerator::_intRange = nullptr;
	std::uniform_real_distribution<float>* RandomNumberGenerator::_floatRange = nullptr;

	void RandomNumberGenerator::InitRandomEngineGenerater(){
		_myEngine = nullptr;
		_myEngine = new std::default_random_engine();
		_myEngine->seed(time(nullptr));
		_intRange = nullptr;
		_floatRange = nullptr;
	}

	void RandomNumberGenerator::SetFloatRange(float min, float max){
		bool isSame = false;

		if (_floatRange != nullptr){
			if((_floatRange->min() == min) && (_floatRange->max() == max)){
				isSame = true;
			}
		}

		if(!isSame){
			delete _floatRange;
			_floatRange = new std::uniform_real_distribution<float>(min, max);
		}
	}

	void RandomNumberGenerator::SetIntRange(int min, int max){
		bool isSame = false;

		if (_intRange != nullptr){
			if ((_intRange->min() == min) && (_intRange->max() == max)){
				isSame = true;
			}
		}

		if (!isSame){
			delete _intRange;
			_intRange = new std::uniform_int_distribution<int>(min, max);
		}
	}

	int RandomNumberGenerator::GetIntValue(){
		return (*_intRange)(*_myEngine);
	}

	float RandomNumberGenerator::GetFloatValue(){
		return (*_floatRange)(*_myEngine);
	}

	void RandomNumberGenerator::FreeRandomEngineGenerater(){
		delete _myEngine;
	}
}
