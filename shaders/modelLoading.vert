#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
//    mat4 model = mat4(vec4(0.200000, 0.000000, 0.000000, 0.000000), vec4(0.000000, 0.200000, 0.000000, 0.000000), vec4(0.000000, 0.000000, 0.200000, 0.000000), vec4(0.000000, -1.750000, 0.000000, 1.000000));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
