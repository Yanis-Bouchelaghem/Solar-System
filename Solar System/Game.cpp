#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "objload.h"
#include <glm/gtc/matrix_transform.hpp>
Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    monkey("..\\Resources\\Objects\\monke.obj")
{
}

void Game::Tick()
{
    window.ClearBuffers();  //Clears the color and depth buffers.
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
    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));
    Model = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));
    Model = glm::rotate(Model, glm::radians(150.0f), glm::vec3(0.f, 1.0f, 0.0f));
    Model = glm::rotate(Model, glm::radians(0.f), glm::vec3(1.f, 0.0f, 0.0f));
    unsigned int matrixID = glGetUniformLocation(shaderProgram.GetID(), "Model");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &Model[0][0]); //Send transformation shaders.
}

void Game::Draw()
{
    //Drawing goes here
    window.UseShader(shaderProgram);
    window.DrawActor(monkey);
}
