#pragma once

//Represents a texture and handles its loading from disk.
class Texture
{
public:
	Texture(const char* texturePath);
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