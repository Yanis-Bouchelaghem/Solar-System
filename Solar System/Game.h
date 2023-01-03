#pragma once
#include <string>
#include "Window.h"
#include "ShaderProgram.h"
#include "Actor.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
//A class that represents the game simulation and handles the logic/render loop.
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
	Window window;	//Window must be constructed first, it initializes OpenGL context and GLFW window.
private:
	ShaderProgram shaderProgram;
	Camera camera;
	glm::vec2 lastMousePosition;
	//Load meshes.
	Mesh sphereMesh;
	//Load textures.
	Texture sunTexture;
	Texture mercuryTexture;
	Texture venusTexture;
	Texture earthTexture;
	Texture marsTexture;
	Texture jupiterTexture;
	Texture saturnTexture;
	Texture uranusTexture;
	Texture neptuneTexture;
	Texture skyboxTexture;
	//Create actors.
	Actor sun;
	Actor mercury;
	Actor venus;
	Actor earth;
	Actor mars;
	Actor jupiter;
	Actor saturn;
	Actor uranus;
	Actor neptune;
	Actor skyBox;
};