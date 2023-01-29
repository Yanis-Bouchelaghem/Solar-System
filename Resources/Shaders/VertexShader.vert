#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;

out vec2 textureCoordinate;
out vec3 normal;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPosition, 1.0);
    textureCoordinate = aTexture;
    normal = aNormal;
}