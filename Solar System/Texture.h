#pragma once

//Represents a texture and handles its loading from disk.
class Texture
{
public:
	Texture(const char* texturePath);					//Load the texture data from disk.
	Texture(const Texture& other) = delete;				//No copy construction allowed.
	Texture& operator=(const Texture& other) = delete;	//No copy assignment allowed.
	~Texture() noexcept;								//Free the OpenGL texture object.
	unsigned int GetID() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetChannelsCount() const;
private:
	unsigned int textureID = -1;
	int width;
	int height;
	int channelsCount;
};