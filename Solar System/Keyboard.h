#pragma once
#include <glfw3.h>
//Represents and manages the states of the keys on a keyboard.
class Keyboard
{
public:
	Keyboard(GLFWwindow& window);
	bool IsKeyPressed(int key) const;	//Returns true if key is currently being pressed.
	bool IsKeyPressedOnce(int key);		//Returns true when key is pressed, then false until the key is released and pressed again.
private:
	GLFWwindow& window;
	bool keyPressed[349] = { false };
};