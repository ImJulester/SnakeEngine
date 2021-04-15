#include "window.h"


Window::Window()
{
	window = nullptr;
	game = nullptr;
	renderer = nullptr;
}

Window::Window(Game* g)
{
	window = nullptr;
	renderer = nullptr;
	game = g;
}

Window::~Window()
{
}

void Window::CreateWindow(int w, int h, const char* title)
{

	if(!glfwInit())
	{
		std::cout << "failed to initialize glfw" << std::endl;
	}
	window = glfwCreateWindow(w, h, title, NULL, NULL);
	if(!window)
	{
		std::cout << " failed to create window" << std::endl;
	}

	glfwMakeContextCurrent(window);
	glewInit();

	width = w;
	height = h;
	renderer = new Renderer(width,height);
	renderer->Start();
	Start();


}

void Window::Start()
{
	while (!glfwWindowShouldClose(window))
	{
		//Update Game first 
		game->Update();
		renderer->Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
}

