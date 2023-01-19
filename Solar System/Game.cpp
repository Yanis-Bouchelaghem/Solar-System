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
    skyboxTexture(settings::texturesPath + "stars_milkyway.jpg")
{
    lastMousePosition = window.GetMousePosition();
    lastTime = window.GetElapsedTime();
    skyBox.ApplyScale(glm::vec3{ settings::cameraFarPlaneDistance });
    //Load the textures and initialize the planets.
    //Sun
    planetTextures.emplace_back(settings::texturesPath + "sun.jpg");
    planets.emplace_back(0.f, settings::sunScale, 0.f, settings::sunRotationSpeed);
    //Mercury
    planetTextures.emplace_back(settings::texturesPath + "mercury.jpg");
    planets.emplace_back(settings::mercuryOrbitRadius, settings::mercuryScale, settings::mercuryOrbitSpeed, settings::mercuryRotationSpeed);
    //Venus
    planetTextures.emplace_back(settings::texturesPath + "venus.jpg");
    planets.emplace_back(settings::venusOrbitRadius, settings::venusScale, settings::venusOrbitSpeed, -settings::venusRotationSpeed);
    //Earth
    planetTextures.emplace_back(settings::texturesPath + "earth.jpg");
    planets.emplace_back(settings::earthOrbitRadius, settings::earthScale, settings::earthOrbitSpeed, settings::earthRotationSpeed);
    //Mars
    planetTextures.emplace_back(settings::texturesPath + "mars.jpg");
    planets.emplace_back(settings::marsOrbitRadius, settings::marsScale, settings::marsOrbitSpeed, settings::marsRotationSpeed);
    //Jupiter
    planetTextures.emplace_back(settings::texturesPath + "jupiter.jpg");
    planets.emplace_back(settings::jupiterOrbitRadius, settings::jupiterScale, settings::jupiterOrbitSpeed, settings::jupiterRotationSpeed);
    //Saturn
    planetTextures.emplace_back(settings::texturesPath + "saturn.jpg");
    planets.emplace_back(settings::saturnOrbitRadius, settings::saturnScale, settings::saturnOrbitSpeed, settings::saturnRotationSpeed);
    //Uranus
    planetTextures.emplace_back(settings::texturesPath + "uranus.jpg");
    planets.emplace_back(settings::uranusOrbitRadius, settings::uranusScale, settings::uranusOrbitSpeed, -settings::uranusRotationSpeed);
    //Neptune
    planetTextures.emplace_back(settings::texturesPath + "neptune.jpg");
    planets.emplace_back(settings::neptuneOrbitRadius, settings::neptuneScale, settings::neptuneOrbitSpeed, settings::neptuneRotationSpeed);
}

void Game::Tick()
{
    //Measure the time that passed since the last frame.
    float now = window.GetElapsedTime();
    float deltatime = lastTime - now;
    lastTime = now;

    window.ClearBuffers();  //Clears the color and depth buffers.
    Update(deltatime);
    Draw(deltatime);
    window.SwapBuffers();	//Swap the current buffer to display it.
    window.PollEvents();    //Process the pending window events.
}

bool Game::ShouldClose() const
{
    return window.ShouldClose();
}

void Game::Update(float deltatime)
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
    
    //Update the planets' transforms.
    for (Planet& planet : planets)
    {
        planet.Update(deltatime);
    }
}

void Game::Draw(float deltatime)
{
    //Drawing goes here.
    glm::mat4 projection = camera.GetPerspectiveMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();

    window.UseShader(shaderProgram);
    unsigned int MVPUniform = shaderProgram.GetUniformID("MVP");
    //Draw the planets
    for (int i = 0; i < planets.size(); ++i)
    {
        shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * planets[i].GetModelMatrix());
        window.DrawActor(sphereMesh, planetTextures[i]);
    }
    //Draw skybox.
    viewMatrix = glm::mat4(glm::mat3(viewMatrix));//Remove the translation from the view matrix, we do not want our skybox to move around.
    shaderProgram.SendUniform<glm::mat4>(MVPUniform, projection * viewMatrix * skyBox.GetModelMatrix());
    window.DrawActor(sphereMesh, skyboxTexture);

}
