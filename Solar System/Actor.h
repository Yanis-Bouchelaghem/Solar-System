#pragma once
#include <vector>

class Actor
{
public:
	Actor(const char* objectPath);
	Actor(const Actor& other) = delete;
	Actor& operator=(const Actor& other) = delete;
	virtual ~Actor() noexcept;
	void Draw() const;
private:
	unsigned int vertexCount;
	//The buffers for the object.
	unsigned int VAO;
	unsigned int VBOVertex;
	unsigned int VBOTexture;
	unsigned int VBONormals;
};