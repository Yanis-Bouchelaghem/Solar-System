#pragma once
#include <string>
#include "glm/glm.hpp"
//Settings that can be tweaked.
namespace settings
{
	//Directory paths.
	inline std::string texturesPath = "..\\Resources\\Textures\\";
	inline std::string meshesPath = "..\\Resources\\Meshes\\";
	inline std::string shadersPath = "..\\Resources\\Shaders\\";
	//Simulation settings.
	//Radiuses
	inline constexpr float earthOrbitRadius = 300.0f;		//The radius of the earth around the sun (other planet's radiuses are scaled based on this value).
	inline constexpr float mercuryOrbitRadius = earthOrbitRadius * 0.6f;
	inline constexpr float venusOrbitRadius = earthOrbitRadius * 0.8f;
	inline constexpr float marsOrbitRadius = earthOrbitRadius * 1.3f;
	inline constexpr float jupiterOrbitRadius = earthOrbitRadius * 1.6f;
	inline constexpr float saturnOrbitRadius = earthOrbitRadius * 2.3f;
	inline constexpr float uranusOrbitRadius = earthOrbitRadius * 2.6f;
	inline constexpr float neptuneOrbitRadius = earthOrbitRadius * 3.3f;
	//Scales
	inline constexpr float sunScale = 100.f;				
	inline constexpr float earthScale = 10.f;				//The scale of the earth (other planet's scales are adjusted based on this value).
	inline constexpr float mercuryScale = earthScale * 0.3f;
	inline constexpr float venusScale = earthScale * 0.9f;	
	inline constexpr float marsScale = earthScale * 0.5f;	
	inline constexpr float jupiterScale = earthScale * 5.0f;
	inline constexpr float saturnScale = earthScale * 4.0f;	
	inline constexpr float uranusScale = earthScale * 2.5f;	
	inline constexpr float neptuneScale = earthScale * 2.3f;
	//Orbit speeds (in degrees per second).
	inline constexpr float earthOrbitSpeed = 20.f;	//The number of degrees the earth should travel around its orbit every second (other planet's orbit speeds are adjusted based on this value).
	inline constexpr float mercuryOrbitSpeed = earthOrbitSpeed * 0.241f;
	inline constexpr float venusOrbitSpeed = earthOrbitSpeed * 0.616f;
	inline constexpr float marsOrbitSpeed = earthOrbitSpeed * 1.882f;
	inline constexpr float jupiterOrbitSpeed = earthOrbitSpeed * 11.87f;
	inline constexpr float saturnOrbitSpeed = earthOrbitSpeed * 29.476f;
	inline constexpr float uranusOrbitSpeed = earthOrbitSpeed * 84.073f;
	inline constexpr float neptuneOrbitSpeed = earthOrbitSpeed * 164.904f;
	//Rotation Speeds (in degrees per second).
	inline constexpr float earthRotationSpeed = 20.f;
	inline constexpr float sunRotationSpeed = earthRotationSpeed * 27;	//The number of degrees the earth should rotate around itself every second (other planet's rotation speeds are adjusted based on this value).
	inline constexpr float mercuryRotationSpeed = earthRotationSpeed * 0.058f;
	inline constexpr float venusRotationSpeed = earthRotationSpeed * 0.243f;
	inline constexpr float marsRotationSpeed = earthRotationSpeed * 1.041;
	inline constexpr float jupiterRotationSpeed = earthRotationSpeed * 0.416;
	inline constexpr float saturnRotationSpeed = earthRotationSpeed * 0.458;
	inline constexpr float uranusRotationSpeed = earthRotationSpeed * 0.708;
	inline constexpr float neptuneRotationSpeed = earthRotationSpeed * 0.666;
	//Keyboard bindings (US layout, use https://www.glfw.org/docs/3.3/group__keys.html for looking up the key's values).
	inline constexpr int forwardKey = 87;		//W
	inline constexpr int leftKey = 65;			//A
	inline constexpr int backwardKey = 83;		//S
	inline constexpr int rightKey = 68;			//D
	inline constexpr int upKey = 69;			//Q
	inline constexpr int downKey = 81;			//E
	inline constexpr int exitKey = 256;			//Escape

	//Default window values.
	inline constexpr int windowWidth = 1280;				//The width of the window.
	inline constexpr int windowHeight = 720;				//The height of the window.
	inline constexpr int viewportX = 0;						//The left x-coordinate of the viewport rectangle (from left of window).
	inline constexpr int viewportY = 0;						//The bottom y-coordinate of the viewport rectangle (from bottom of window).
	inline constexpr int viewportWidth = 1280;				//The width of the viewport rectangle (from left of window).
	inline constexpr int viewportHeight = 720;				//The height of the viewport rectangle (from bottom of window).
	inline constexpr char windowTitle[] = "Solar system";	//The title of the window.
	inline constexpr bool captureMouse = true;				//Whether or not the window should capture the mouse.

	//Default camera values.
	inline constexpr glm::vec3 cameraInitialPosition = { 0.0f, 0.0f, 150.0f }; //The initial position of the camera in world space.
	inline constexpr float cameraYaw = -90.0f;				//The yaw of the camera.
	inline constexpr float cameraPitch = 0.0f;				//The pitch of the camera.
	inline constexpr float cameraSpeed = 30.0f;				//The speed of the camera's movement.
	inline constexpr float cameraSensitivity = 0.05f;		//The sensitivity of the mouse.
	inline constexpr float cameraFOV = 45.0f;				//The field of view.
	inline constexpr float cameraNearPlaneDistance = 0.3f;	//The distance of the near plane from the camera.
	inline constexpr float cameraFarPlaneDistance = 10000.0f;//The distance of the far plane from the camera.
	inline constexpr float cameraMaxPitch = 70.0f;			//Sets the camera's maximum pitch (when looking up and down).

	//Precalculate some values for convenience.
	inline constexpr float screenRatio = float(windowWidth) / float(windowHeight);

	//Check that the settings make sense.
	static_assert(windowWidth > 0 && windowHeight > 0);		//Window width/height must be positive non-zeroes.
	static_assert(viewportWidth > 0 && viewportHeight > 0);	//Viewport width/height must be positive non-zeroes.
	static_assert(cameraNearPlaneDistance > 0.0f);			//Near plane distance must be a positive non-zero.
	static_assert(cameraNearPlaneDistance < cameraFarPlaneDistance);//Near plane must be "nearer" than the far plane.
	static_assert(cameraSensitivity > 0.0f);				//Sensitivity must be a positive non-zero.
}