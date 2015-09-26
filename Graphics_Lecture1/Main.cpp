//
#include <iostream>
#include <string>
//
#include <SDL/SDL.h>
#include <GL/glew.h>
//
#include "MainGame.h"
//
#include <glm/glm.hpp>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv){
	MainGame mygame;
	mygame.Run();
	cout << "Enter any key to quit..." << endl;
	int a;
	cin >> a;
	return a;
}