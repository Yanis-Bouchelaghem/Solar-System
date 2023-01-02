#pragma once
#include <glm/glm.hpp>

// A camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices.
class Camera
{
public:
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods.
    enum class Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
public:
    Camera(glm::vec3 position, glm::vec3 worldUp, float movementSpeed, float yaw, float pitch, float mouseSensitivity, float zoom);
    
    glm::mat4 GetViewMatrix() const; //returns the view matrix calculated using Euler Angles and the LookAt Matrix.
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Movement direction, float deltaTime);
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
private:
    void UpdateCameraVectors(); //Calculates the front vector from the Camera's (updated) Euler Angles
private:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler Angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
};

