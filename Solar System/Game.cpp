#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "Settings.h"
//TODO : Remove matrix transform when done with it.
#include <glm/gtc/matrix_transform.hpp>

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    camera(settings::cameraInitialPosition, {0.0f, 1.0f, 0.0f}, settings::cameraSpeed,
        settings::cameraYaw, settings::cameraPitch, settings::cameraSensitivity, settings::cameraZoom),
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

    //Drawing goes here
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    unsigned int modelMatrixUniformID = shaderProgram.GetUniformID("Model");
    window.UseShader(shaderProgram);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * monkey.GetModelMatrix());
    window.DrawActor(monkey);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * sphere.GetModelMatrix());
    window.DrawActor(sphere);
}
