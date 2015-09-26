#include "MainGame.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <MyEngine/FatalErrors.h>
#include <MyEngine/ImageLoader.h>
#include <MyEngine/Window.h>
#include <MyEngine/Camera2D.h>
#include <MyEngine/ResourceManager.h>
#include <MyEngine/Timing.h>

#include <iostream>
#include <string>

#include "Bullet.h"

MainGame::MainGame(): _screenWidth(1024/2), _screenHeight(1435/2), _gameState(GameState::PLAY), _maxFPS(60.0f){
	_camera.Init(_screenWidth, _screenHeight);
}
MainGame::~MainGame(){}

void MainGame::Run(){
	_InitSystems();
	
	_GameLoop();
}

void MainGame::_InitSystems(){
	MyEngine::Init();

	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);

	_InitShaders();

	_spriteBatch.Init();

	_fpsLimiter.Init(_maxFPS);

	std::printf("***  OpenGL Version: %s ***\n", glGetString(GL_VERSION));
}

void MainGame::_InitShaders(){
	_colorProgram.CompileShaders("Shaders/ColorShading.vert", "Shaders/ColorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.AddAttribute("vertexUV");
	_colorProgram.LinkShaders();
	
}

void MainGame::_GameLoop(){
	
	while (_gameState != GameState::EXIT){
		_fpsLimiter.BeginFrame();

		//ProcessInput
		_ProcessInput();

		_camera.Update();
		for (int i = 0; i < _bullets.size();){
			if (_bullets[i].Update()){
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}else{
				//only increment i if we do not delete bullet.
				i++;
			}
		}

		//Drawing the game
		_DrawGame();

		//Calculating the FPS.
		_fps = _fpsLimiter.End();

		//print only once 10 frames
		const int printFrequency = 10000;
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter >= printFrequency){
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::_ProcessInput(){
	SDL_Event tempEvent;

	const float CAMERA_MOVE_SPD = 2.0f;
	const float CAMERA_SCALE_SPD = 0.1f;

	// only accept mouse move event and exit windows event.
	while (SDL_PollEvent(&tempEvent)){
		switch (tempEvent.type){
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				_inputManager.PressKey(tempEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.ReleaseKey(tempEvent.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.PressKey(tempEvent.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.ReleaseKey(tempEvent.button.button);
				break;
			case SDL_MOUSEMOTION:
				_inputManager.SetMouseCoords(tempEvent.motion.x, tempEvent.motion.y);
				break;
		}
	}

	//check throughInputManager
	float temp = 0.0f;
	if (_inputManager.IsKeyPressed(SDLK_w)){
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, CAMERA_MOVE_SPD));
	}
	if (_inputManager.IsKeyPressed(SDLK_s)){
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -CAMERA_MOVE_SPD));
	}
	if (_inputManager.IsKeyPressed(SDLK_a)){
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_MOVE_SPD, 0.0f));
	}
	if (_inputManager.IsKeyPressed(SDLK_d)){
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(+CAMERA_MOVE_SPD, 0.0f));
	}
	if (_inputManager.IsKeyPressed(SDLK_q)){
		temp = _camera.GetScale() + CAMERA_SCALE_SPD;
		_camera.SetScale(temp);
	}
	if (_inputManager.IsKeyPressed(SDLK_e)){
		temp = _camera.GetScale() + (-CAMERA_SCALE_SPD);
		_camera.SetScale(temp);
	}

	if (_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)){
		glm::vec2 tempMouseCoord = _camera.ConvertScreenToWorld(_inputManager.GetMouseCoords());
		std::cout << tempMouseCoord.x << " " << tempMouseCoord.y << std::endl;

		glm::vec2 playerPos(0.0f);
		glm::vec2 direction = tempMouseCoord - playerPos;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPos, direction, 5.0f, 500);
	}

}

void MainGame::_DrawGame(){

	//set base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//use the color program
	_colorProgram.use();
	
	glActiveTexture(GL_TEXTURE0);

	//Find the Location of the uniform variable "mySampler" in fragment shadder
	GLint textureLocation = _colorProgram.GetUniformLocation("mySampler");
	//Set the int type uniform variable value to 0 
	glUniform1i(textureLocation, 0);

	//Find the Location of the uniform variable "orthoMatrix" in vertex shadder
	GLuint orthoMatrixLocation = _colorProgram.GetUniformLocation("orthoMatrix");
	//set the camera matrix
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();

	glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	_spriteBatch.Begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static MyEngine::GLTextrue myTexture = MyEngine::ResourceManager::GetTexture("Texture/ship.png");
	MyEngine::Color myColor;
	myColor.r = 255;
	myColor.g = 255;
	myColor.b = 255;
	myColor.a = 255;
	//Add all the data that needs to be draw to the buffer
	_spriteBatch.Draw(pos, uv, myTexture._id, 0.0f, myColor);

	for (std::vector<Bullet>::iterator i = _bullets.begin(); i < _bullets.end(); i++){
		i->Draw(_spriteBatch);
	}

	_spriteBatch.End();
	_spriteBatch.RenderBatche();

	//Unbind the 2D type texture.
	glBindTexture(GL_TEXTURE_2D , 0);
	//Unuse the color program.
	_colorProgram.unuse();

	//Swap buffer and draw everything to the screen
	_window.SwapBuffer();
}
