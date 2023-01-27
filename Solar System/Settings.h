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
	//Radiuses.
	inline constexpr float earthOrbitRadius = 300.0f;		//The radius of the earth around the sun (other planet's radiuses are scaled based on this value).
	inline constexpr float mercuryOrbitRadius = earthOrbitRadius * 0.6f;
	inline constexpr float venusOrbitRadius = earthOrbitRadius * 0.8f;
	inline constexpr float marsOrbitRadius = earthOrbitRadius * 1.3f;
	inline constexpr float jupiterOrbitRadius = earthOrbitRadius * 2.0f;
	inline constexpr float saturnOrbitRadius = earthOrbitRadius * 3.0f;
	inline constexpr float uranusOrbitRadius = earthOrbitRadius * 3.8f;
	inline constexpr float neptuneOrbitRadius = earthOrbitRadius * 4.3f;

	//Scales.
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
	inline constexpr float mercuryOrbitSpeed = earthOrbitSpeed * 4.149f;
	inline constexpr float venusOrbitSpeed = earthOrbitSpeed * 1.623f;
	inline constexpr float marsOrbitSpeed = earthOrbitSpeed * 0.531f;
	inline constexpr float jupiterOrbitSpeed = earthOrbitSpeed * 0.084f;
	inline constexpr float saturnOrbitSpeed = earthOrbitSpeed * 0.033f;
	inline constexpr float uranusOrbitSpeed = earthOrbitSpeed * 0.011f;
	inline constexpr float neptuneOrbitSpeed = earthOrbitSpeed * 0.006f;

	//Rotation Speeds (in degrees per second).
	inline constexpr float earthRotationSpeed = 50.f;
	inline constexpr float sunRotationSpeed = earthRotationSpeed * 0.037f;	//The number of degrees the earth should rotate around itself every second (other planet's rotation speeds are adjusted based on this value).
	inline constexpr float mercuryRotationSpeed = earthRotationSpeed * 17.241f;
	inline constexpr float venusRotationSpeed = -earthRotationSpeed * 4.115f;	//Rotates the other way compared to earth.
	inline constexpr float marsRotationSpeed = earthRotationSpeed * 0.960f;
	inline constexpr float jupiterRotationSpeed = earthRotationSpeed * 2.403f;
	inline constexpr float saturnRotationSpeed = earthRotationSpeed * 2.183f;
	inline constexpr float uranusRotationSpeed = -earthRotationSpeed * 1.412f;	//Rotates the other way compared to earth.
	inline constexpr float neptuneRotationSpeed = earthRotationSpeed * 1.501f;

	//Time settings.
	inline constexpr float timeAdjustSpeed = 0.1f;

	//Keyboard bindings (US layout, use https://www.glfw.org/docs/3.3/group__keys.html for looking up the key's values).
	inline constexpr int forwardKey = 87;		//W
	inline constexpr int leftKey = 65;			//A
	inline constexpr int backwardKey = 83;		//S
	inline constexpr int rightKey = 68;			//D
	inline constexpr int upKey = 69;			//Q
	inline constexpr int downKey = 81;			//E
	inline constexpr int wireframeModeKey = 84;	//T
	inline constexpr int cameraSpeedupKey = 86;	//V
	inline constexpr int cameraSlowdownKey = 67;//C
	inline constexpr int pauseKey = 80;			//P
	inline constexpr int timeSpeedupKey = 334;	//Keypad ADD
	inline constexpr int timeSlowdownKey = 333;	//Keypad SUBTRACT
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
	inline constexpr glm::vec3 cameraInitialPosition = { 0.0f, 0.0f, 1000.0f }; //The initial position of the camera in world space.
	inline constexpr float cameraYaw = -90.0f;				//The yaw of the camera.
	inline constexpr float cameraPitch = 0.0f;				//The pitch of the camera.
	inline constexpr float cameraSpeed = 100.0f;			//The speed of the camera's movement.
	inline constexpr float cameraSensitivity = 0.05f;		//The sensitivity of the mouse.
	inline constexpr float cameraFOV = 45.0f;				//The field of view.
	inline constexpr float cameraNearPlaneDistance = 0.3f;	//The distance of the near plane from the camera.
	inline constexpr float cameraFarPlaneDistance = 10000.0f;//The distance of the far plane from the camera.
	inline constexpr float cameraMaxPitch = 70.0f;			//Sets the camera's maximum pitch (when looking up and down).
	inline constexpr float cameraSpeedupRate = 50.0f;		//The amount of speed that gets added/subtracted when the camera speeds up or slows down.

	//Precalculate some values for convenience.
	inline constexpr float screenRatio = float(windowWidth) / float(windowHeight);

	//Check that the settings make sense.
	static_assert(windowWidth > 0 && windowHeight > 0);		//Window width/height must be positive non-zeroes.
	static_assert(viewportWidth > 0 && viewportHeight > 0);	//Viewport width/height must be positive non-zeroes.
	static_assert(cameraNearPlaneDistance > 0.0f);			//Near plane distance must be a positive non-zero.
	static_assert(cameraNearPlaneDistance < cameraFarPlaneDistance);//Near plane must be "nearer" than the far plane.
	static_assert(cameraSensitivity > 0.0f);				//Sensitivity must be a positive non-zero.
}