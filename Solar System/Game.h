#pragma once
#include <string>
#include "Window.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, struct GLFWmonitor* monitor = nullptr, struct GLFWwindow* share = nullptr);
	void Tick();				//Updates the game and draws a frame.
	bool ShouldClose() const;	//Returns whether or not the window is flagged for closing.
private:
	void Update();
	void Draw();
private:
	//Window must be constructed first, it initializes OpenGL context and GLFW window.
	Window window;
};