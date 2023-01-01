#pragma once
#include <vector>
#include <glm/glm.hpp>

//A class to represent a drawable entity in the world.
class Actor
{
public:
	Actor(const char* objectPath);
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
	virtual ~Actor() noexcept;
	void ResetModelMatrix();								//Resets the model matrix to the identity matrix.
	void ApplyTranslation(glm::vec3 translation);			//Applies a translation on the model matrix.
	void ApplyScale(glm::vec3 scale);						//Applies a scale on the model matrix.
	void ApplyRotation(float degrees, glm::vec3 axis);		//Applies a rotation on the model matrix.
	const glm::mat4& GetModelMatrix() const;
	unsigned int GetVAO() const;
	unsigned int GetVertexCount() const;
private:
	//The properties of the actor.
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	unsigned int vertexCount;
	//The buffers for the object.
	unsigned int VAO;
	unsigned int VBOVertex;
	unsigned int VBOTexture;
	unsigned int VBONormals;
};