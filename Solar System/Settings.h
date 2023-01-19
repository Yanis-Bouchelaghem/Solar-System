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
	inline constexpr float earthOrbitRadius = 300.0f;		//The radius of the earth around the sun (other planet's radiuses are scaled based on this value).
	inline constexpr float sunScale = 100.f;				//The scale of the sun.
	inline constexpr float earthScale = 10.f;				//The scale of the earth (other planet's scales are adjusted based on this value).
	inline constexpr float mercuryScale = earthScale * 0.3f;//The scale of mercury.
	inline constexpr float venusScale = earthScale * 0.9f;	//The scale of venus.
	inline constexpr float marsScale = earthScale * 0.5f;	//The scale of mars.
	inline constexpr float jupiterScale = earthScale * 5.0f;//The scale of jupiter.
	inline constexpr float saturnScale = earthScale * 4.0f;	//The scale of saturn.
	inline constexpr float uranusScale = earthScale * 2.5f;	//The scale of uranus.
	inline constexpr float neptuneScale = earthScale * 2.3f;//The scale of neptune.
	
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