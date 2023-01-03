#pragma once
#include <string>
#include <memory>
#include <functional>
#include <glm/vec2.hpp>
#include "ShaderProgram.h"
#include "Actor.h"
#include "Mesh.h"
#include "Texture.h"
//A window class that manages the OpenGL context and the GLFW window creation/destruction.
class Window
{
public:
	Window(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, struct GLFWmonitor* monitor = nullptr, struct GLFWwindow* share = nullptr);
	Window(const Window& other) = delete;				//No copy construction allowed.
	Window& operator=(const Window& other) = delete;	//No copy assignment allowed.
	~Window() noexcept;
	void UseShader(const ShaderProgram& shaderProgram);	//Binds the given shader.
	void DrawActor(const Actor& actor, const Mesh& mesh, const Texture& texture);	//Draws actor with the given mesh and texture.
	void DrawActor(const Actor& actor, const Mesh& mesh, const Texture& texture, const ShaderProgram& shaderProgram); //Binds the given shader, then draws actor.
	void ClearBuffers();				//Clears the color and depth buffers.
	void SwapBuffers();					//Swaps the buffers to display a frame.
	void PollEvents() const;			//Processes the pending window events.
	void Close();						//Flags the window for closing.
	bool ShouldClose() const;			//Returns whether or not the window is flagged for closing.
	bool IsKeyPressed(int key) const;	//Returns whether or not the given key is currently pressed.
	double GetElapsedTime() const;		//Returns the time elapsed since the creation of the window (in seconds).
	glm::vec2 GetMousePosition() const;	//Returns the mouse position in screen coordinates.
private:
	//The GLFW window is a third party struct that lacks a destructor, so a unique pointer is used to safely manage
	//it and automatically destroy it using a custom deleter. Preventing any potential memory leaks.
	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};