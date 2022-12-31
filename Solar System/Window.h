#pragma once
#include <string>
#include <memory>
#include <functional>

//A window class that manages the OpenGL context and the GLFW window creation/destruction.
class Window
{
public:
	Window(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, struct GLFWmonitor* monitor = nullptr, struct GLFWwindow* share = nullptr);
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	~Window() noexcept;

	void ClearBuffers() const;	//Clears the color and depth buffers.
	void SwapBuffers() const;	//Swaps the buffers to display the frame.
	bool ShouldClose() const;	//Returns whether or not the window is flagged for closing.
private:
	//The window is a third party struct that lacks a destructor, so a unique pointer is used to safely manage
	//it and automatically destroy it using a custom deleter. Preventing any potential memory leaks.
	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};