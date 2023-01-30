#include "Game.h"
#include "Settings.h"

Game::Game(int windowWidth, int windowHeight, int viewportX, int viewportY, int viewportWidth, int viewportHeight, const std::string title, GLFWmonitor* monitor, GLFWwindow* share)
    :
    window(windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, title, monitor, share),
    defaultShader(settings::shadersPath + "default.vert", settings::shadersPath + "default.frag"),
    noLightShader(settings::shadersPath + "noLight.vert", settings::shadersPath + "noLight.frag"),
    earthShader(settings::shadersPath + "earth.vert", settings::shadersPath + "earth.frag"),
    camera(settings::cameraInitialPosition, settings::cameraSpeed, settings::cameraYaw,
        settings::cameraPitch, settings::cameraMaxPitch, settings::cameraSensitivity, settings::cameraFOV,
        settings::screenRatio, settings::cameraNearPlaneDistance, settings::cameraFarPlaneDistance),
    sphereMesh(settings::meshesPath + "sphere.obj"),
    earthNightTexture(settings::texturesPath + "earth_night.jpg"),
    skyboxTexture(settings::texturesPath + "stars_milkyway.jpg")
{
    lastMousePosition = window.GetMousePosition();
    lastTime = window.GetElapsedTime();
    skyBox.ApplyScale(glm::vec3{ settings::cameraFarPlaneDistance });
    //Load the textures and initialize the planets.
    //Sun
    planetTextures.emplace_back(settings::texturesPath + "sun.jpg");
    planets.emplace_back(0.f, settings::sunScale, 0.f, settings::sunRotationSpeed);
    //Earth
    planetTextures.emplace_back(settings::texturesPath + "earth.jpg");
    planets.emplace_back(settings::earthOrbitRadius, settings::earthScale, settings::earthOrbitSpeed, settings::earthRotationSpeed);
    //Mercury
    planetTextures.emplace_back(settings::texturesPath + "mercury.jpg");
    planets.emplace_back(settings::mercuryOrbitRadius, settings::mercuryScale, settings::mercuryOrbitSpeed, settings::mercuryRotationSpeed);
    //Venus
    planetTextures.emplace_back(settings::texturesPath + "venus.jpg");
    planets.emplace_back(settings::venusOrbitRadius, settings::venusScale, settings::venusOrbitSpeed, settings::venusRotationSpeed);
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
    planets.emplace_back(settings::uranusOrbitRadius, settings::uranusScale, settings::uranusOrbitSpeed, settings::uranusRotationSpeed);
    //Neptune
    planetTextures.emplace_back(settings::texturesPath + "neptune.jpg");
    planets.emplace_back(settings::neptuneOrbitRadius, settings::neptuneScale, settings::neptuneOrbitSpeed, settings::neptuneRotationSpeed);
    //Setup the lighting in the shaders.
    window.UseShader(defaultShader);
    defaultShader.SendUniform<glm::vec3>("lightPosition", { 0.0f,0.0f,0.0f });
    defaultShader.SendUniform<glm::vec3>("ambientColor", settings::ambientColor);
    defaultShader.SendUniform<glm::vec3>("sunlightColor", settings::sunlightColor);
    window.UseShader(earthShader);
    earthShader.SendUniform<glm::vec3>("ambientColor", settings::earthAmbientColor);
    earthShader.SendUniform<glm::vec3>("sunlightColor", settings::sunlightColor);
    earthShader.SendUniform<glm::vec3>("lightPosition", { 0.0f,0.0f,0.0f });
    earthShader.SendUniform<float>("specularStrength", settings::earthSpecularStrength);
    earthShader.SendUniform<int>("textureSampler1", 0); //Assign locations to the texture samplers.
    earthShader.SendUniform<int>("textureSampler2", 1);
}

void Game::Tick()
{
    //Measure the time that has passed since the previous frame.
    float now = window.GetElapsedTime();
    float deltatime = now - lastTime;
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
    //Logic update happens here.
    //Check if window should be closed.
    if(window.IsKeyPressed(settings::exitKey))
    {
        window.Close();
    }
    //Update camera rotation.
    glm::vec2 mousePosition = window.GetMousePosition();
    glm::vec2 cameraRotationOffset{mousePosition.x - lastMousePosition.x, lastMousePosition.y - mousePosition.y };
    lastMousePosition = mousePosition;
    camera.Rotate(cameraRotationOffset);
    //Update camera position.
    if (window.IsKeyPressed(settings::forwardKey))
        camera.Move(Camera::Movement::FORWARD, deltatime);
    if (window.IsKeyPressed(settings::backwardKey))
        camera.Move(Camera::Movement::BACKWARD, deltatime);
    if (window.IsKeyPressed(settings::leftKey))
        camera.Move(Camera::Movement::LEFT, deltatime);
    if (window.IsKeyPressed(settings::rightKey))
        camera.Move(Camera::Movement::RIGHT, deltatime);
    if (window.IsKeyPressed(settings::upKey1) || window.IsKeyPressed(settings::upKey2))
        camera.Move(Camera::Movement::UP, deltatime);
    if (window.IsKeyPressed(settings::downKey))
        camera.Move(Camera::Movement::DOWN, deltatime);
    //Update wireframe mode.
    if (window.IsKeyPressedOnce(settings::wireframeModeKey))
    {
        window.ToggleWireframe();
    }
    //Update camera speed.
    if (window.IsKeyPressedOnce(settings::cameraSpeedupKey))
    {
        camera.AddMovementSpeed(settings::cameraSpeedupRate);
    }
    if (window.IsKeyPressedOnce(settings::cameraSlowdownKey))
    {
        camera.AddMovementSpeed(-settings::cameraSpeedupRate);
    }
    if (window.IsKeyPressedOnce(settings::pauseKey))
    {
        isPaused = !isPaused;
    }

    if (!isPaused)
    {
        //Update the planets' transforms.
        for (Planet& planet : planets)
        {
            planet.Update(deltatime * timeSpeed);
        }

        //Update the time speed.
        if (window.IsKeyPressed(settings::timeSpeedupKey))
            timeSpeed += settings::timeAdjustSpeed;
        if (window.IsKeyPressed(settings::timeSlowdownKey))
            timeSpeed -= settings::timeAdjustSpeed;
    }
}

void Game::Draw(float deltatime)
{
    //Drawing happens here.
    glm::mat4 projection = camera.GetPerspectiveMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    //Draw the planets (except for the sun and the earth) using the default shader (normal lighting).
    window.UseShader(defaultShader);
    for (size_t i = 2; i < planets.size(); ++i)
    {
        defaultShader.SendUniform<glm::mat4>("MVP", projection * viewMatrix * planets[i].GetModelMatrix());
        defaultShader.SendUniform<glm::mat4>("modelMatrix", planets[i].GetModelMatrix());
        defaultShader.SendUniform<glm::mat3>("normalMatrix", planets[i].GetNormalMatrix());
        window.DrawActor(sphereMesh, planetTextures[i]);
    }
    //Draw the earth using its own shader.
    window.UseShader(earthShader);
    earthShader.SendUniform<glm::mat4>("MVP", projection * viewMatrix * planets[1].GetModelMatrix());
    earthShader.SendUniform<glm::mat4>("modelMatrix", planets[1].GetModelMatrix());
    earthShader.SendUniform<glm::mat3>("normalMatrix", planets[1].GetNormalMatrix());
    earthShader.SendUniform<glm::vec3>("viewPosition", camera.GetPosition());
    window.DrawActor(sphereMesh, planetTextures[1], earthNightTexture);
    //Draw the sun and the skybox without lighting.
    window.UseShader(noLightShader);
    //Draw sun.
    noLightShader.SendUniform<glm::mat4>("MVP", projection * viewMatrix * planets[0].GetModelMatrix());
    window.DrawActor(sphereMesh, planetTextures[0]);
    //Draw skybox.
    viewMatrix = glm::mat4(glm::mat3(viewMatrix));//Remove the translation from the view matrix, we do not want our skybox to move around.
    noLightShader.SendUniform<glm::mat4>("MVP", projection * viewMatrix * skyBox.GetModelMatrix());
    window.DrawActor(sphereMesh, skyboxTexture);
}
