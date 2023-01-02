#include "Game.h"
#include "Settings.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    camera(settings::cameraInitialPosition, {0.0f, 1.0f, 0.0f}, settings::cameraSpeed, settings::cameraYaw,
        settings::cameraPitch, settings::cameraSensitivity, settings::cameraFOV, settings::screenRatio),
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
    window.PollEvents();    //Process the pending window events.
}

bool Game::ShouldClose() const
{
    return window.ShouldClose();
}

void Game::Update()
{
    //Logic goes here.

    //Update camera position based on input.
    if (window.IsKeyPressed(settings::forwardKey))
    {
        camera.Move(Camera::Movement::FORWARD, 0.016f);
    }    
    if (window.IsKeyPressed(settings::backwardKey))
    {
        camera.Move(Camera::Movement::BACKWARD, 0.016f);
    }
    if (window.IsKeyPressed(settings::leftKey))
    {
        camera.Move(Camera::Movement::LEFT, 0.016f);
    } 
    if (window.IsKeyPressed(settings::rightKey))
    {
        camera.Move(Camera::Movement::RIGHT, 0.016f);
    }
    if (window.IsKeyPressed(settings::upKey))
    {
        camera.Move(Camera::Movement::UP, 0.016f);
    }
    if (window.IsKeyPressed(settings::downKey))
    {
        camera.Move(Camera::Movement::DOWN, 0.016f);
    }
    monkey.ResetModelMatrix();
    monkey.ApplyTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
    monkey.ApplyRotation(0.0f, glm::vec3(0.f, 1.0f, 0.0f));

    sphere.ResetModelMatrix();
    sphere.ApplyRotation(float(window.GetElapsedTime()) * 180, glm::vec3(0.f, 1.0f, 0.f));
    sphere.ApplyTranslation(glm::vec3(2.5f, 0.0f, 0.0f));

}

void Game::Draw()
{
    //Drawing goes here.
    glm::mat4 projection = camera.GetPerspectiveMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    window.UseShader(shaderProgram);
    unsigned int modelMatrixUniformID = shaderProgram.GetUniformID("MVP");
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * monkey.GetModelMatrix());
    window.DrawActor(monkey);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * sphere.GetModelMatrix());
    window.DrawActor(sphere);
}
