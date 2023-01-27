#include "Keyboard.h"
#include <glfw3.h>

Keyboard::Keyboard(GLFWwindow& window)
	:
	window(window)
{
}

bool Keyboard::IsKeyPressed(int key) const
{
	return glfwGetKey(&window, key) == GLFW_PRESS;
}

bool Keyboard::IsKeyPressedOnce(int key)
{
	if (IsKeyPressed(key))
	{
		if (keyPressed[key])
		{
			return false;
		}
		else
		{
			keyPressed[key] = true;
			return true;
		}
	}
	else
	{
		keyPressed[key] = false;
	}
}
