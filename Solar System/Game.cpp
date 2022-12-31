#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "objload.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag")
{
    loadOBJ("..\\Resources\\Objects\\cube.obj", vertexPositions, textureCoordinates, normals);

}

void Game::Tick()
{
    window.ClearBuffers();
    Update();
    Draw();
    window.SwapBuffers();	//Swap the current buffer to display it.
    glfwPollEvents();
}

bool Game::ShouldClose() const
{
    return window.ShouldClose();
}

void Game::Update()
{
    //Logic goes here
}

void Game::Draw()
{
    //Drawing goes here
    shaderProgram.Use();
}
