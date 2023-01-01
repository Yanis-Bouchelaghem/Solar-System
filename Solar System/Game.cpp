#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    monkey("..\\Resources\\Objects\\monke.obj"),
    sphere("..\\Resources\\Objects\\sphere.obj")
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
    monkey.ResetModelMatrix();
    monkey.ApplyTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
    monkey.ApplyScale(glm::vec3(0.2f, 0.2f, 0.2f));
    monkey.ApplyRotation(150.0f, glm::vec3(0.f, 1.0f, 0.0f));

    sphere.ResetModelMatrix();
    sphere.ApplyRotation(float(window.GetElapsedTime()) * 180, glm::vec3(0.f, 1.0f, 0.f));
    sphere.ApplyTranslation(glm::vec3(0.7f, 0.0f, 0.0f));
    sphere.ApplyScale(glm::vec3(0.2f, 0.2f, 0.2f));
    sphere.ApplyRotation(-float(window.GetElapsedTime()) * 180, glm::vec3(0.f, 1.0f, 0.f));

}

void Game::Draw()
{
    unsigned int matrixID = glGetUniformLocation(shaderProgram.GetID(), "Model");
    //Drawing goes here
    window.UseShader(shaderProgram);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &monkey.GetModelMatrix()[0][0]); //Send transformation shaders.
    window.DrawActor(monkey);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &sphere.GetModelMatrix()[0][0]); //Send transformation shaders.
    window.DrawActor(sphere);
}
