#version 330 core

in vec2 textureCoordinate;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform vec3 sunlightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform float specularStrength;
uniform sampler2D textureEarth;
uniform sampler2D textureEarthNight;

void main()
{
    //Calculate the diffuse color.
    vec3 normalizedNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);  
    float diffuseStrength = max(dot(normalizedNormal, lightDirection), 0.0);
    vec3 diffuseColor = diffuseStrength * sunlightColor;

    //Calculate the specular color.
    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-lightDirection, normalizedNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specularColor = specularStrength * spec * sunlightColor; 

    //Calculate the day/night texture mix.
    vec4 dayNightMix = mix(texture(textureEarthNight, textureCoordinate), texture(textureEarth, textureCoordinate), diffuseStrength);
    
    //Calculate the final color (ambient + diffuse + specular).
    FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0) * dayNightMix;
}

