#pragma once
#include <string>
#include "Window.h"
#include "ShaderProgram.h"
#include "Actor.h"
#include "Planet.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include <vector>
//A class that represents the game simulation and handles the logic/render loop.
class Game
{
public:
	Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, struct GLFWmonitor* monitor = nullptr, struct GLFWwindow* share = nullptr);
	void Tick();				//Updates the game and draws a frame.
	bool ShouldClose() const;	//Returns whether or not the window is flagged for closing.
private:
	void Update(float deltatime);
	void Draw(float deltatime);
private:
	Window window;	//Window must be constructed first, it initializes OpenGL context and GLFW window.
private:
	ShaderProgram defaultShader;
	ShaderProgram noLightShader;
	ShaderProgram earthShader;
	Camera camera;
	Mesh sphereMesh;
	std::vector<Texture> planetTextures;
	std::vector<Planet> planets;
	Texture earthNightTexture;
	Texture earthSpecularTexture;
	Actor skyBox;
	Texture skyboxTexture;
	glm::vec2 lastMousePosition;
	float lastTime;
	float timeSpeed = 1.0f;
	bool isPaused = false;
};