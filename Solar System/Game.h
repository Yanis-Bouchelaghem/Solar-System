#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include <memory>
#include <functional>
#include <string>

class Game
{
public:
	Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight,
		const std::string title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game() noexcept;

	void Tick();
	bool ShouldClose() const;
private:
	void Update();
	void Draw();
private:
	//The window is a third party struct that lacks a destructor, so a unique pointer is used to safely manage
	//it and automatically destroy it using a custom deleter. Preventing any potential memory leaks.
	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};