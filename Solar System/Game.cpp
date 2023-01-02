#include "Game.h"
#include "Settings.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    camera(settings::cameraInitialPosition, {0.0f, 1.0f, 0.0f}, settings::cameraSpeed, settings::cameraYaw,
        settings::cameraPitch, settings::cameraMaxPitch, settings::cameraSensitivity, settings::cameraFOV,
        settings::screenRatio, settings::cameraNearPlaneDistance, settings::cameraFarPlaneDistance),
    earthTexture("..\\Resources\\Textures\\earth.jpg"),
    monkey("..\\Resources\\Objects\\monke.obj", earthTexture),
    sphere("..\\Resources\\Objects\\sphere.obj", earthTexture),
    dome("..\\Resources\\Objects\\sphere.obj", earthTexture)
{
    lastMousePosition = window.GetMousePosition();
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
    //Calculate camera rotation.
    glm::vec2 mousePosition = window.GetMousePosition();
    glm::vec2 cameraRotationOffset{mousePosition.x - lastMousePosition.x, lastMousePosition.y - mousePosition.y };
    lastMousePosition = mousePosition;
    camera.Rotate(cameraRotationOffset);
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
    monkey.ApplyTranslation({ 0.0f, 0.0f, 0.0f });
    monkey.ApplyRotation(0.0f, { 0.f, 1.0f, 0.0f });

    sphere.ResetModelMatrix();
    sphere.ApplyRotation(float(window.GetElapsedTime()) * 180, { 0.f, 1.0f, 0.f });
    sphere.ApplyTranslation({ 2.5f, 0.0f, 0.0f });

    dome.ResetModelMatrix();
    dome.ApplyScale(glm::vec3{ 100.0f });

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
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * dome.GetModelMatrix());
    window.DrawActor(dome);

}
