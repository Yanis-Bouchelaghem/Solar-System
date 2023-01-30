#pragma once
#include <glm/glm.hpp>

// A camera class that handles and calculates both the projection and view matrices.
class Camera
{
public:
    static constexpr glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods.
    enum class Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
public:
    Camera(glm::vec3 position, float movementSpeed, float yaw, float pitch, float maxPitch,
        float mouseSensitivity, float zoom, float screenRatio, float nearPlaneDistance = 0.1f, float farPlaneDistance = 100.f);
    glm::mat4 GetViewMatrix() const;        //Returns the view matrix calculated using Euler Angles and the LookAt Matrix.
    glm::mat4 GetPerspectiveMatrix() const; //Returns the perspective matrix using the current zoom, ratio and near/far plane properties.
    void Move(Movement direction, float deltaTime); //Moves the camera in the given direction.
    void Rotate(glm::vec2 rotationOffset, bool constrainPitch = true);//Rotates the camera according to a given rotation.
    void AddMovementSpeed(float speed);     //Adds the given speed to the movement of the camera (speed cannot be reduced below 0).
    const glm::vec3& GetPosition() const;
private:
    void UpdateCameraVectors(); //Calculates the front vector from the Camera's (updated) Euler Angles
private:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up;
    glm::vec3 right;
    // euler Angles
    float yaw;
    float pitch;
    float maxPitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    float screenRatio;
    float nearPlaneDistance;
    float farPlaneDistance;
};

