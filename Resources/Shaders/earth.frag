#version 330 core

in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

uniform sampler2D textureSampler1;
uniform sampler2D textureSampler2;

uniform vec3 ambientColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragmentPosition);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0,1.0,1.0);

    FragColor = vec4(ambientColor + diffuse,1.0) * mix(texture(textureSampler2, textureCoordinate), texture(textureSampler1, textureCoordinate), diff);
}

