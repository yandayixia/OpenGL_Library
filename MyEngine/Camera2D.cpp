#include "Camera2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine{

	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{}

	Camera2D::~Camera2D(){}

	void Camera2D::Init(int screenWidth, int screenHeight){
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::Update(){
		if (_needsMatrixUpdate){
			//Move the camera's coordinates
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Scale the camera, zoom in/out
			glm::vec3 scale(_scale, _scale, 0.0f); //The larger the scale, the more zoomed in camer is.
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}
	}


	bool Camera2D::IsBoxInView(const glm::vec2 & position, const glm::vec2 & dimesion){
		glm::vec2 scaledScreenDimension = glm::vec2(_screenWidth, _screenHeight) / (_scale);

		//The minimum distance before collision happens
		const float MIN_DISTANCE_X = (dimesion.x / 2.0f) + scaledScreenDimension.x / 2.0f;
		const float MIN_DISTANCE_Y = (dimesion.y / 2.0f) + scaledScreenDimension.y / 2.0f;

		const glm::vec2 centerOfTarget = position + (dimesion / 2.0f);
		const glm::vec2 centerOfCamera = _position;
		const glm::vec2 distVec = centerOfTarget - centerOfCamera;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if ((xDepth > 0) && (yDepth > 0)){
			//if there is a collision
			return true;
		}
		return false;
	}

	//setters
	void Camera2D::SetPosition(glm::vec2& newPosition){
		_position = newPosition;
		_needsMatrixUpdate = true;
	}

	void Camera2D::SetScale(float& newScale){
		_scale = newScale;
		_needsMatrixUpdate = true;
	}

	//getters
	glm::vec2 Camera2D::GetPosition(){
		return _position;
	}
	float Camera2D::GetScale(){
		return _scale;
	}
	glm::mat4 Camera2D::GetCameraMatrix(){
		return _cameraMatrix;
	}


	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords){
		//invert y_Coord
		screenCoords.y = _screenHeight - screenCoords.y;
		//(0,0) in the center
		screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);
		//scale the coordinates
		screenCoords /= _scale;
		//translate with the camera
		screenCoords += _position;
		return screenCoords;
	}

}