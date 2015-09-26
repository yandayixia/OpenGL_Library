#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine{
	class Camera2D
	{
		// the CENTER position of the camera
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
		bool _needsMatrixUpdate;
		int _screenWidth, _screenHeight;

	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);
		void Update();

		bool IsBoxInView(const glm::vec2 & position, const glm::vec2 & dimesion);

		//setters
		void SetPosition(glm::vec2& newPosition);
		void SetScale(float& newScale);

		//getters
		glm::vec2 GetPosition();
		float GetScale();
		glm::mat4 GetCameraMatrix();
		
		glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);
	};
}