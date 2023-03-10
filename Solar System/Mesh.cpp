#include "Mesh.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include "objload.h"

Mesh::Mesh(std::string meshPath)
{
	//Load the object's vertex data from disk.
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<glm::vec3> normals;
	loadOBJ(meshPath.c_str(), vertexPositions, textureCoordinates, normals);
	//Save the number of vertices.
	vertexCount = (int)vertexPositions.size();
	assert(vertexCount >= 3); //If assertion fails : Object could not be loaded or it does not contain enough vertices.
	//Setup the buffers for this object.
	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBOVertex
	glGenBuffers(1, &VBOVertex);
	glBindBuffer(GL_ARRAY_BUFFER, VBOVertex);
	glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(glm::vec3), vertexPositions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//VBOTexture
	glGenBuffers(1, &VBOTexture);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexture);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(glm::vec2), textureCoordinates.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	//VBONormals
	glGenBuffers(1, &VBONormals);
	glBindBuffer(GL_ARRAY_BUFFER, VBONormals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(2);
}

Mesh::Mesh(Mesh&& other) noexcept
	:
	VAO(other.VAO),
	VBOVertex(other.VBOVertex),
	VBOTexture(other.VBOTexture),
	VBONormals(other.VBONormals),
	vertexCount(other.vertexCount)
{
	other.VAO = 0;
	other.VBOVertex = 0;
	other.VBOTexture = 0;
	other.VBONormals = 0;
	other.vertexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other)
	{
		//Free the data held by this object.
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBOVertex);
		glDeleteBuffers(1, &VBOTexture);
		glDeleteBuffers(1, &VBONormals);
		//Pilfer the data from the other object.
		VAO = other.VAO;
		VBOVertex = other.VBOVertex;
		VBOTexture = other.VBOTexture;
		VBONormals = other.VBONormals;
		vertexCount = other.vertexCount;
		other.VAO = 0;
		other.VBOVertex = 0;
		other.VBOTexture = 0;
		other.VBONormals = 0;
		other.vertexCount = 0;
	}
	return *this;
}

Mesh::~Mesh() noexcept
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBOVertex);
		glDeleteBuffers(1, &VBOTexture);
		glDeleteBuffers(1, &VBONormals);
	}
}

unsigned int Mesh::GetVAO() const
{
	return VAO;
}

int Mesh::GetVertexCount() const
{
	return vertexCount;
}
