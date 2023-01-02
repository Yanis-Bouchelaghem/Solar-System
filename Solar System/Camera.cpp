#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float movementSpeed, float yaw, float pitch,
    float mouseSensitivity, float zoom, float screenRatio, float nearPlaneDistance, float farPlaneDistance)
    :
    position(position),
    worldUp(worldUp),
    yaw(yaw),
    pitch(pitch),
    movementSpeed(movementSpeed),
    mouseSensitivity(mouseSensitivity),
    zoom(zoom),
    screenRatio(screenRatio),
    nearPlaneDistance(nearPlaneDistance),
    farPlaneDistance(farPlaneDistance)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetPerspectiveMatrix() const
{
    return glm::perspective(glm::radians(zoom), screenRatio, nearPlaneDistance, farPlaneDistance);
}

void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == Movement::FORWARD)
        position += front * velocity;
    if (direction == Movement::BACKWARD)
        position -= front * velocity;
    if (direction == Movement::LEFT)
        position -= right * velocity;
    if (direction == Movement::RIGHT)
        position += right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
