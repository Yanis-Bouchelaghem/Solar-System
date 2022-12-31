#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include <memory>
#include <functional>
#include <string>

class Game
{
public:
	Game(int width, int height, const std::string title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
private:
	//The window is a third party struct that lacks a destructor, so a unique pointer is used to safely manage
	//it and automatically destroy it using a custom deleter. Preventing any potential memory leaks.
	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};