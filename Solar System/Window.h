#pragma once
#include <string>
#include <memory>
#include <functional>
#include "Actor.h"
#include "ShaderProgram.h"
//A window class that manages the OpenGL context and the GLFW window creation/destruction.
class Window
{
public:
	Window(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, struct GLFWmonitor* monitor = nullptr, struct GLFWwindow* share = nullptr);
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	~Window() noexcept;

	void UseShader(const ShaderProgram& shaderProgram);	//Binds the given shader.
	void DrawActor(const Actor& actor);	//Draws an actor with the currently bound shader.
	void DrawActor(const Actor& actor, const ShaderProgram& shaderProgram); //Binds the given shader, then draws actor.
	void ClearBuffers();		//Clears the color and depth buffers.
	void SwapBuffers();			//Swaps the buffers to display the frame.
	bool ShouldClose() const;	//Returns whether or not the window is flagged for closing.
private:
	//The GLFW window is a third party struct that lacks a destructor, so a unique pointer is used to safely manage
	//it and automatically destroy it using a custom deleter. Preventing any potential memory leaks.
	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};