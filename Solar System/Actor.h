#pragma once
#include <vector>

//A class to represent a drawable entity in the world.
class Actor
{
public:
	Actor(const char* objectPath);
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
	virtual ~Actor() noexcept;

	unsigned int GetVAO() const;
	unsigned int GetVertexCount() const;
private:
	unsigned int vertexCount;
	//The buffers for the object.
	unsigned int VAO;
	unsigned int VBOVertex;
	unsigned int VBOTexture;
	unsigned int VBONormals;
};