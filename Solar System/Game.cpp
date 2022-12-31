#include "Game.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

Game::Game(int width, int height, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
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
    window.reset(glfwCreateWindow(width, height, title.c_str(), monitor, share));
    if (window == nullptr)
    {
        std::cout << "Failed to init GLFW.\n";
        glfwTerminate();
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
    glViewport(0, 0, 800, 600);
    //Set the background clear color.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //Set the window resize callback function
    glfwSetFramebufferSizeCallback(window.get(),
        [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });
}

Game::~Game() noexcept
{
    window.reset();		//Release and safely destroy the window (via the unique pointer deleter).
    glfwTerminate();
}
