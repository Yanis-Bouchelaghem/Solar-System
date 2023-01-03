#include "Texture.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(std::string texturePath)
{
    //Create a texture buffer.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //Set the texture wrapping/filtering options.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load and generate the texture.
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channelsCount, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture." << texturePath << std::endl;
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);
}

Texture::~Texture() noexcept
{
    glDeleteTextures(1, &textureID);
}

unsigned int Texture::GetID() const
{
    return textureID;
}

int Texture::GetWidth() const
{
    return width;
}

int Texture::GetHeight() const
{
    return height;
}

int Texture::GetChannelsCount() const
{
    return channelsCount;
}
