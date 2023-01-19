#include "Planet.h"

Planet::Planet(float orbitRadius, float scale, float orbitSpeedDegrees, float rotationSpeedDegrees)
	:
	orbitRadius(orbitRadius),
	scale(scale),
	orbitSpeedDegrees(orbitSpeedDegrees),
	rotationSpeedDegrees(rotationSpeedDegrees)
{
}

void Planet::Update(float deltatime)
{
	currentRotationDegrees += rotationSpeedDegrees * deltatime;
	currentOrbitDegrees += orbitSpeedDegrees * deltatime;
	//Clamp the values to 360 degrees.
	if (currentRotationDegrees > 360.0f)
		currentRotationDegrees = currentRotationDegrees - 360.0f;
	else if (currentRotationDegrees < -360.0f)
		currentRotationDegrees = currentRotationDegrees + 360.0f;

	if (currentOrbitDegrees > 360.0f)
		currentOrbitDegrees = currentOrbitDegrees - 360.0f;
	else if (currentOrbitDegrees < -360.0f)
		currentOrbitDegrees = currentOrbitDegrees + 360.0f;
	//Calculate planet transforms.
	ResetModelMatrix();
	ApplyRotation(currentOrbitDegrees, { 0.f,1.f,0.f });// Rotates around the sun.
	ApplyTranslation({ orbitRadius, 0.0f, 0.0f });
	ApplyScale(glm::vec3{ scale });
	ApplyRotation(currentRotationDegrees, {0.f,1.f,0.f}); //Revolves clockwise around itself.
}
