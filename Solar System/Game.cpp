#include "Game.h"
#include "Settings.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram("..\\Resources\\Shaders\\VertexShader.vert", "..\\Resources\\Shaders\\FragmentShader.frag"),
    camera(settings::cameraInitialPosition, {0.0f, 1.0f, 0.0f}, settings::cameraSpeed, settings::cameraYaw,
        settings::cameraPitch, settings::cameraMaxPitch, settings::cameraSensitivity, settings::cameraFOV,
        settings::screenRatio, settings::cameraNearPlaneDistance, settings::cameraFarPlaneDistance),
    sphereMesh("..\\Resources\\Meshes\\sphere.obj"),
    sunTexture("..\\Resources\\Textures\\sun.jpg"),
    earthTexture("..\\Resources\\Textures\\earth.jpg"),
    skyboxTexture("..\\Resources\\Textures\\stars_milkyway.jpg")
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
    //Check if window should be closed.
    if(window.IsKeyPressed(settings::exitKey))
    {
        window.Close();
    }
    //Calculate camera rotation.
    glm::vec2 mousePosition = window.GetMousePosition();
    glm::vec2 cameraRotationOffset{mousePosition.x - lastMousePosition.x, lastMousePosition.y - mousePosition.y };
    lastMousePosition = mousePosition;
    camera.Rotate(cameraRotationOffset);
    ///////////////////////////TODO : Implement deltatime.
    //Update camera position based on input.
    if (window.IsKeyPressed(settings::forwardKey))
        camera.Move(Camera::Movement::FORWARD, 0.016f);
    if (window.IsKeyPressed(settings::backwardKey))
        camera.Move(Camera::Movement::BACKWARD, 0.016f);
    if (window.IsKeyPressed(settings::leftKey))
        camera.Move(Camera::Movement::LEFT, 0.016f);
    if (window.IsKeyPressed(settings::rightKey))
        camera.Move(Camera::Movement::RIGHT, 0.016f);
    if (window.IsKeyPressed(settings::upKey))
        camera.Move(Camera::Movement::UP, 0.016f);
    if (window.IsKeyPressed(settings::downKey))
        camera.Move(Camera::Movement::DOWN, 0.016f);
    
    sun.ResetModelMatrix();
    sun.ApplyRotation(float(window.GetElapsedTime() * 20), { 0.f, 1.0f, 0.0f });
    sun.ApplyScale({ 5.0f, 5.0f, 5.0f });

    earth.ResetModelMatrix();
    earth.ApplyRotation(float(window.GetElapsedTime()) * 90, { 0.f, 1.0f, 0.f });
    earth.ApplyTranslation({ 10.0f, 0.0f, 0.0f });

    skyBox.ResetModelMatrix();
    skyBox.ApplyScale(glm::vec3{ 100.0f });

}

void Game::Draw()
{
    //Drawing goes here.
    glm::mat4 projection = camera.GetPerspectiveMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    window.UseShader(shaderProgram);
    unsigned int modelMatrixUniformID = shaderProgram.GetUniformID("MVP");
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * sun.GetModelMatrix());
    window.DrawActor(sun, sphereMesh, sunTexture);
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * earth.GetModelMatrix());
    window.DrawActor(earth, sphereMesh, earthTexture);
    viewMatrix = glm::mat4(glm::mat3(viewMatrix));//Remove the translation from the view matrix, we do not want our skybox to move around.
    shaderProgram.SendUniform<glm::mat4>(modelMatrixUniformID, projection * viewMatrix * skyBox.GetModelMatrix());
    window.DrawActor(skyBox, sphereMesh, skyboxTexture);

}
