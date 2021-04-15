#pragma once

#include "Renderer.h"


#include <iostream>

#include "Game.h"

class Window
{
public:

	Window();
	Window(Game* g);

	~Window();

	void CreateWindow(int width, int height, const char* title);
	void Start();

private:

	GLFWwindow* window;
	Game* game;
	Renderer* renderer;

	float width;
	float height;
	
};