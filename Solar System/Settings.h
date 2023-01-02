#pragma once
#include "glm/glm.hpp"
//Settings that can be tweaked.
namespace settings
{
	//Default window values.
	inline constexpr int windowWidth = 800;					//The width of the window.
	inline constexpr int windowHeight = 600;				//The height of the window.
	inline constexpr int viewportX = 0;						//The left x-coordinate of the viewport rectangle.
	inline constexpr int viewportY = 0;						//The left y-coordinate of the viewport rectangle.
	inline constexpr int viewportWidth = 800;				//The width of the viewport rectangle.
	inline constexpr int viewportHeight = 600;				//The height of the viewport rectangle.
	inline constexpr char windowTitle[] = "Solar system";	//The title of the window.

	//Default camera values.
	inline constexpr glm::vec3 cameraInitialPosition = { 0.0f, 0.0f, 10.0f }; //The initial position of the camera in world space.
	inline constexpr float cameraYaw = -90.0f;				//The yaw of the camera.
	inline constexpr float cameraPitch = 0.0f;				//The pitch of the camera.
	inline constexpr float cameraSpeed = 2.5f;				//The speed of the camera's movement.
	inline constexpr float cameraSensitivity = 0.1f;		//The sensitivity of the mouse.
	inline constexpr float cameraFOV = 45.0f;				//The field of view.
	inline constexpr float cameraNearPlaneDistance = 0.1f;	//The distance of the near plane from the camera.
	inline constexpr float cameraFarPlaneDistance = 100.0f;	//The distance of the far plane from the camera.

	//Precalculate some values for convenience.
	inline constexpr float screenRatio = float(windowWidth) / float(windowHeight);
}