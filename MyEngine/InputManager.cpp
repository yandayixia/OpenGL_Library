#include "InputManager.h"
#include <unordered_map>

namespace MyEngine{
	InputManager::InputManager() :_mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	//Updates the _prevKeyMap.
	void InputManager::UpDate(){
		for (std::unordered_map<unsigned int, bool>::iterator i = _keyMap.begin(); i != _keyMap.end(); i++){
			_prevKeyMap[i->first] = i->second;
		}
	}


	void InputManager::PressKey(unsigned int keyID){
		_keyMap[keyID] = true;
	}

	void InputManager::ReleaseKey(unsigned int keyID){
		_keyMap[keyID] = false;
	}

	void InputManager::SetMouseCoords(float x, float y){
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	glm::vec2 InputManager::GetMouseCoords() const {
		return _mouseCoords;
	}

	bool InputManager::IsKeyDown(unsigned int keyID){
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()){
			return it->second;
		}
		else{
			return false;
		}
	}

	bool InputManager::WasKeyDown(unsigned int keyID){
		auto it = _prevKeyMap.find(keyID);
		if (it != _prevKeyMap.end()){
			return it->second;
		}
		else{
			return false;
		}
	}

	//returns true if the key is just pressed
	bool InputManager::IsKeyPressed(unsigned int keyID){
		//check if the key is pressed this frame but not last frame.
		bool isPressed = false;
	
		if ((IsKeyDown(keyID) == true) && (WasKeyDown(keyID) == false)){
			UpDate();
			return true;
		}

		return false;

	}
	
}