#pragma once

//Represents a mesh, handles the loading from disk.
class Mesh
{
public:
	Mesh(const char* meshPath);					//Loads the vertex, texture and normal data from disk.
	Mesh(const Mesh& other) = delete;			//No copy construction allowed.
	Mesh& operator=(const Mesh& other) = delete;//No copy assignment allowed.
	~Mesh() noexcept;							//Frees the vertex, texture and normal VBOs.
	unsigned int GetVAO() const;
	int GetVertexCount() const;
private:
	int vertexCount;
	//The buffers for the mesh.
	unsigned int VAO;
	unsigned int VBOVertex;
	unsigned int VBOTexture;
	unsigned int VBONormals;
};