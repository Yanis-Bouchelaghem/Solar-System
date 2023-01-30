#version 330 core

in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

uniform sampler2D textureSampler;
uniform vec3 ambientColor;
uniform vec3 lightPosition;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosition - fragmentPosition);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0,1.0,1.0);

    FragColor = vec4(ambientColor + diffuse,1.0) * texture(textureSampler, textureCoordinate);
}

