#pragma once
#include <assert.h>
#include "glm/glm.hpp"
#include <glad/glad.h>
#include <string>
//A class that represents a shader program, manages the loading from disk, compiling and linking of shaders.
//Also manages the uniform attributes of the shader program.
class ShaderProgram
{
public:
	ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);//Compiles and links the shaders.
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;
	~ShaderProgram() noexcept;
	unsigned int GetUniformID(const char* uniformName) const;	//Returns the identifier of the given uniform.
	unsigned int GetID() const;	//Returns the shader program ID generated by OpenGL.
public:
	//Define the uniform sending functions using some elegant templating.
	template<typename T>
	void SendUniform(unsigned int uniformID, const T& value)
	{
		assert(false); //Trying to send an unsupported type.
	}
	//Template specializations.
	template<>
	void SendUniform<glm::mat4>(unsigned int uniformID, const glm::mat4& value) //Send a matrix of dimension 4.
	{
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, &value[0][0]);
	}
	template<>
	void SendUniform<glm::mat3>(unsigned int uniformID, const glm::mat3& value)
	{
		glUniformMatrix3fv(uniformID, 1, GL_FALSE, &value[0][0]);
	}
	template<>
	void SendUniform<glm::vec3>(unsigned int uniformID, const glm::vec3& value) //Send a vector of dimension 3.
	{
		glUniform3fv(uniformID, 1, &value[0]);
	}
	template<>
	void SendUniform<unsigned int>(unsigned int uniformID, const unsigned int& value) //Send an unsigned integer.
	{
		glUniform1ui(uniformID, value);
	}
private:
	unsigned int shaderProgramID;
};