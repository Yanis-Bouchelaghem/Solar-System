#include "Game.h"
#include "Settings.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    shaderProgram(settings::shadersPath + "VertexShader.vert", settings::shadersPath + "FragmentShader.frag"),
    camera(settings::cameraInitialPosition, settings::cameraSpeed, settings::cameraYaw,
        settings::cameraPitch, settings::cameraMaxPitch, settings::cameraSensitivity, settings::cameraFOV,
        settings::screenRatio, settings::cameraNearPlaneDistance, settings::cameraFarPlaneDistance),
    sphereMesh(settings::meshesPath + "sphere.obj"),
    //Load meshes.
    sunTexture(settings::texturesPath + "sun.jpg"),
    mercuryTexture(settings::texturesPath + "mercury.jpg"),
    venusTexture(settings::texturesPath + "venus.jpg"),
    earthTexture(settings::texturesPath + "earth.jpg"),
    marsTexture(settings::texturesPath + "mars.jpg"),
    jupiterTexture(settings::texturesPath + "jupiter.jpg"),
    saturnTexture(settings::texturesPath + "saturn.jpg"),
    uranusTexture(settings::texturesPath + "uranus.jpg"),
    neptuneTexture(settings::texturesPath + "neptune.jpg"),
    skyboxTexture(settings::texturesPath + "stars_milkyway.jpg")
{
    lastMousePosition = window.GetMousePosition();
    skyBox.ApplyScale(glm::vec3{ settings::cameraFarPlaneDistance });
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
    
    //Calculate sun transforms.
    sun.ResetModelMatrix();
    sun.ApplyRotation(float(window.GetElapsedTime() * 5), Camera::worldUp); //Revolves around itself.
    sun.ApplyScale(glm::vec3{100.0f});
    //Calculate earth transforms.
    earth.ResetModelMatrix();
    earth.ApplyRotation(float(window.GetElapsedTime()) * 20, Camera::worldUp); //Rotates around the sun.
    earth.ApplyTranslation({ settings::earthOrbitRadius, 0.0f, 0.0f });
    earth.ApplyScale(glm::vec3{ settings::earthScale });
    earth.ApplyRotation(float(window.GetElapsedTime()) * 20, Camera::worldUp); //Revolves around itself.
    //Calculate mercury transforms.
    mercury.ResetModelMatrix();
    mercury.ApplyRotation(float(window.GetElapsedTime()) * 50, Camera::worldUp);// Rotates around the sun.
    mercury.ApplyTranslation({ settings::earthOrbitRadius * 0.6f, 0.0f, 0.0f });
    mercury.ApplyScale(glm::vec3{ settings::mercuryScale });
    mercury.ApplyRotation(float(window.GetElapsedTime()) * 90, Camera::worldUp); //Revolves around itself.


}

void Game::Draw()
{
    //Drawing goes here.
    glm::mat4 projection = camera.GetPerspectiveMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    window.UseShader(shaderProgram);
    unsigned int MVPUniform = shaderProgram.GetUniformID("MVP");
    //Draw sun.
    shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * sun.GetModelMatrix());
    window.DrawActor(sun, sphereMesh, sunTexture);
    //Draw earth.
    shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * earth.GetModelMatrix());
    window.DrawActor(earth, sphereMesh, earthTexture);
    //Draw mercury.
    shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * mercury.GetModelMatrix());
    window.DrawActor(mercury, sphereMesh, mercuryTexture);
    //Draw skybox.
    viewMatrix = glm::mat4(glm::mat3(viewMatrix));//Remove the translation from the view matrix, we do not want our skybox to move around.
    shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * skyBox.GetModelMatrix());
    window.DrawActor(skyBox, sphereMesh, skyboxTexture);

}
