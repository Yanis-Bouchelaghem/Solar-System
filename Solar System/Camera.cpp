#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float movementSpeed, float yaw, float pitch, float maxPitch,
    float mouseSensitivity, float zoom, float screenRatio, float nearPlaneDistance, float farPlaneDistance)
    :
    position(position),
    worldUp(worldUp),
    yaw(yaw),
    pitch(pitch),
    maxPitch(maxPitch),
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

void Camera::Move(Movement direction, float deltaTime)
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
    if (direction == Movement::UP)
        position += up * velocity;
    if (direction == Movement::DOWN)
        position -= up * velocity;
}

void Camera::Rotate(glm::vec2 rotationOffset, bool constrainPitch)
{
    rotationOffset *= mouseSensitivity;
    yaw += rotationOffset.x;
    pitch += rotationOffset.y;
    //Constrain the pitch so that the screen doesn't get flipped.
    if (constrainPitch)
    {
        if (pitch > maxPitch)
            pitch = maxPitch;
        if (pitch < -maxPitch)
            pitch = -maxPitch;
    }
    //Update front, right and up vectors using the updated Euler angles.
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
    //Re-calculate the front vector.
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    //Re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));//normalize the vectors, because their length gets closer to 0 the more we look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
