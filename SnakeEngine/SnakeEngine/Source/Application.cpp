
#include "Window.h"
#include "Game.h"
int main(void)
{
	Game g; 
	Window window = Window(&g);
	window.CreateWindow(640,480, "Snake engine");


	return 0;
}