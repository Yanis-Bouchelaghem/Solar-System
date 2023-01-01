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
    monkeyModel = glm::mat4(1.0f);
    monkeyModel = glm::translate(monkeyModel, glm::vec3(0.0f, 0.0f, 0.0f));
    monkeyModel = glm::scale(monkeyModel, glm::vec3(0.5f, 0.5f, 0.5f));
    monkeyModel = glm::rotate(monkeyModel, glm::radians(150.0f), glm::vec3(0.f, 1.0f, 0.0f));

    sphereModel = glm::mat4(1.0f);
    sphereModel = glm::translate(sphereModel, glm::vec3(0.5f, 0.5f, 0.0f));
    sphereModel = glm::scale(sphereModel, glm::vec3(0.5f, 0.5f, 0.5f));
    sphereModel = glm::rotate(sphereModel, glm::radians(0.0f), glm::vec3(0.f, 1.0f, 0.0f));

}

void Game::Draw()
{
    unsigned int matrixID = glGetUniformLocation(shaderProgram.GetID(), "Model");
    //Drawing goes here
    window.UseShader(shaderProgram);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &monkeyModel[0][0]); //Send transformation shaders.
    window.DrawActor(monkey);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &sphereModel[0][0]); //Send transformation shaders.
    window.DrawActor(sphere);
}
