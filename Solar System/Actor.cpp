#include "Actor.h"
#include <glm/gtc/matrix_transform.hpp>

void Actor::ResetModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);
}

void Actor::ApplyTranslation(glm::vec3 translation)
{
	modelMatrix = glm::translate(modelMatrix, translation);
}

void Actor::ApplyScale(glm::vec3 scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Actor::ApplyRotation(float degrees, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(degrees), axis);
}

const glm::mat4& Actor::GetModelMatrix() const
{
	return modelMatrix;
}

glm::mat3 Actor::GetNormalMatrix() const
{
	return glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
}

