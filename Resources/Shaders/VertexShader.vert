#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexture;
layout (location = 2) in vec3 aNormals;

out vec3 ourColor;

uniform mat4 Model;

void main()
{
    gl_Position = Model * vec4(aPos, 1.0);
    ourColor = aNormals; //For now we are sending the normals as the color
}