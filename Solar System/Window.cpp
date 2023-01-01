#include "Window.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

Window::Window(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(nullptr, [](GLFWwindow* window) { glfwDestroyWindow(window); }) //Set the deleter for the managed window.

{
    //Initialize GLFW.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    //Create a window and set its context to the current thread.
    window.reset(glfwCreateWindow(windowWidth, windowHeight, title.c_str(), monitor, share));
    if (window == nullptr)
    {
        std::cout << "Failed to init GLFW.\n";
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window.get());
    //Get the openGL functions addresses using GLAD.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Set the viewport of the window.
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    //Set the background clear color.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //Enable depth to allow us to remove hidden parts.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //Set the window resize callback function
    glfwSetFramebufferSizeCallback(window.get(),
        [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

Window::~Window() noexcept
{
    window.reset();		//Release and safely destroy the window (via the unique pointer deleter).
    glfwTerminate();
}

void Window::UseShader(const ShaderProgram& shaderProgram)
{
    glUseProgram(shaderProgram.GetID());
}

void Window::DrawActor(const Actor& actor)
{
    glBindVertexArray(actor.GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, actor.GetVertexCount());
}

void Window::DrawActor(const Actor& actor, const ShaderProgram& shaderProgram)
{
    UseShader(shaderProgram);
    DrawActor(actor);
}

void Window::ClearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window.get());
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(window.get());
}

double Window::GetElapsedTime() const
{
    return glfwGetTime();
}
