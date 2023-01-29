#version 330 core
out vec4 FragColor;

in vec2 textureCoordinate;
in vec3 normal;

uniform sampler2D textureSampler;
uniform vec3 ambientColor;

void main()
{
    FragColor = vec4(ambientColor,1.0) * texture(textureSampler, textureCoordinate);
}

