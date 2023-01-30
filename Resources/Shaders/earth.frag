#version 330 core

in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform vec3 sunlightColor;
uniform vec3 lightPosition;
uniform sampler2D textureSampler1;
uniform sampler2D textureSampler2;

void main()
{
    vec3 normalizedNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);  
    float diffuseStrength = max(dot(normalizedNormal, lightDirection), 0.0);
    vec3 diffuseColor = diffuseStrength * sunlightColor;

    FragColor = vec4(ambientColor + diffuseColor,1.0) * mix(texture(textureSampler2, textureCoordinate), texture(textureSampler1, textureCoordinate), diffuseStrength);
}

