#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
//TODO : Remove matrix transform when done with it.
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
    monkey.ResetModelMatrix();
    monkey.ApplyTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
    //monkey.ApplyScale(glm::vec3(0.2f, 0.2f, 0.2f));
    monkey.ApplyRotation(0.0f, glm::vec3(0.f, 1.0f, 0.0f));

    sphere.ResetModelMatrix();
    sphere.ApplyRotation(float(window.GetElapsedTime()) * 180, glm::vec3(0.f, 1.0f, 0.f));
    sphere.ApplyTranslation(glm::vec3(2.5f, 0.0f, 0.0f));
    //sphere.ApplyScale(glm::vec3(0.2f, 0.2f, 0.2f));
    //sphere.ApplyRotation(-float(window.GetElapsedTime()) * 180, glm::vec3(0.f, 1.0f, 0.f));

}

void Game::Draw()
{

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));

    //Drawing goes here
    unsigned int modelMatrixUniformID = shaderProgram.GetUniformID("Model");
    window.UseShader(shaderProgram);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * view * monkey.GetModelMatrix());
    window.DrawActor(monkey);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * view * sphere.GetModelMatrix());
    window.DrawActor(sphere);
}
