#pragma once

#include <SDL/SDL.h>
#include <MyEngine/Sprite.h>
#include <MyEngine/GLSLProgram.h>
#include <MyEngine/GLTexture.h>
#include <MyEngine/Window.h>
#include <MyEngine/MyEngine.h>
#include <MyEngine/Camera2D.h>
#include <MyEngine/SpriteBatch.h>
#include <MyEngine/InputManager.h>
#include <MyEngine/Timing.h>

#include <vector>

#include "Bullet.h"

enum class GameState {PLAY, EXIT};

class MainGame{
	MyEngine::Window _window;
	int _screenWidth, _screenHeight;
	
	GameState _gameState;

	float _maxFPS;
	float _fps;

	MyEngine::GLSLProgram _colorProgram;

	MyEngine::Camera2D _camera;
	MyEngine::SpriteBatch _spriteBatch;

	MyEngine::InputManager _inputManager;
	MyEngine::FpsLimiter _fpsLimiter;


	void _InitSystems();
	void _InitShaders();

	void _GameLoop();
	void _ProcessInput();
	void _DrawGame();

	std::vector<Bullet> _bullets;

public:
	MainGame();
	~MainGame();

	void Run();
};

