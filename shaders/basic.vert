#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 normalFrag;
out mat4 moveNorm;

uniform mat4 modelViewMatrix;

void main()
{
    normalFrag = normal;
    moveNorm = modelViewMatrix;

    vec4 w = vec4(position, 1.0);
    gl_Position = w * modelViewMatrix;
}
