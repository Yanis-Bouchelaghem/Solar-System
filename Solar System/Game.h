#pragma once
#include <string>
#include "Window.h"
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "Actor.h"

//A class that represents the simulation and handles the logic/render loop.
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
	ShaderProgram shaderProgram;
	Actor monkey;

	glm::mat4 Model;
	//Camera
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 camDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr float camSpeed = 0.005f;
};