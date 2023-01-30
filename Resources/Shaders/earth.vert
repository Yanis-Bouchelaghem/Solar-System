#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;

out vec2 textureCoordinate;
out vec3 normal;
out vec3 fragmentPosition;

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

void main()
{
    textureCoordinate = aTexture;
    normal = normalMatrix * aNormal;
    fragmentPosition = vec3(modelMatrix * vec4(aPosition, 1.0));
    gl_Position = MVP * vec4(aPosition, 1.0);
}