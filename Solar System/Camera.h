#pragma once
#include <glm/glm.hpp>

// A camera class that handles and calculates both the projection and view matrices.
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
    Camera(glm::vec3 position, glm::vec3 worldUp, float movementSpeed, float yaw, float pitch,
        float mouseSensitivity, float zoom, float screenRatio, float nearPlaneDistance = 0.1f, float farPlaneDistance = 100.f);
    
    glm::mat4 GetViewMatrix() const;        //Returns the view matrix calculated using Euler Angles and the LookAt Matrix.
    glm::mat4 GetPerspectiveMatrix() const; //Returns the perspective matrix using the current zoom, ratio and near/far plane properties.
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
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
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
    float screenRatio;
    float nearPlaneDistance;
    float farPlaneDistance;
};

