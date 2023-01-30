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
uniform float specularShininess;
uniform sampler2D textureEarth;
uniform sampler2D textureEarthNight;
uniform sampler2D textureSpecular;
uniform sampler2D textureClouds;

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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularShininess);
    vec3 specularColor = (specularStrength * spec * sunlightColor) * vec3(texture(textureSpecular, textureCoordinate)); 

    //Calculate the day/night texture mix.
    vec4 dayNightMix = mix(texture(textureEarthNight, textureCoordinate), texture(textureEarth, textureCoordinate), diffuseStrength);
    //Add the clouds texture.
    vec4 finalMix = dayNightMix + (0.3 * texture(textureClouds, textureCoordinate));

    //Calculate the final color (ambient + diffuse + specular).
    FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0) * finalMix;
}

