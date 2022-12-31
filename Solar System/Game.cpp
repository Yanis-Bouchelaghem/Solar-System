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
    loadOBJ("..\\Resources\\Objects\\monke.obj", vertexPositions, textureCoordinates, normals);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Generate and link the VBO to the VAO.
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Provide the vertices list to openGL.
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(glm::vec3), &vertexPositions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    //Link the second attribute buffer (the color).
    glGenBuffers(1, &VBOColor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOColor);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

    glBindVertexArray(0);

    //Enable depth to allow us to remove hidden parts.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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
    shaderProgram.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexPositions.size());
}
