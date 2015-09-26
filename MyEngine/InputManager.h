#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
namespace MyEngine{

	class InputManager
	{
		glm::vec2 _mouseCoords;
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _prevKeyMap;

		bool WasKeyDown(unsigned int keyID);
	public:
		InputManager();
		~InputManager();

		//Updates the _prevKeyMap.
		void UpDate();

		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);

		void SetMouseCoords(float x, float y);
		glm::vec2 GetMouseCoords() const;

		//returns true if the key is held down.
		bool IsKeyDown(unsigned int keyID);

		//returns true if the key is just pressed
		bool IsKeyPressed(unsigned int keyID);
	};
}