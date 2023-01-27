#pragma once
#include "Actor.h"

//A class that represents a planet and its movement in an orbit.
class Planet : public Actor
{
public:
	/// <param name="orbitRadius">The radius of the orbit around the center of the world.</param>
	/// <param name="scale">The scale of the planet.</param>
	/// <param name="orbitSpeedDegrees">The number of degrees the planet should travel around its orbit every second.</param>
	/// <param name="rotationSpeedDegrees">The number of degrees the planet should rotate around itself every second.</param>
	Planet(float orbitRadius, float scale, float orbitSpeedDegrees, float rotationSpeedDegrees);
	void Update(float deltatime);
private:
	const float orbitRadius;
	const float scale;
	const float orbitSpeedDegrees;
	const float rotationSpeedDegrees;
	float currentOrbitDegrees = 0.f;
	float currentRotationDegrees = 0.f;
};
