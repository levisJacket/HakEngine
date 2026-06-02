#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 worldPosition;
out vec4 worldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main()
{
    vec4 worldPos = vec4(position, 1.0) * modelMatrix; 
    worldPosition = worldPos;

    vec4 worldNorm = vec4(normal, 1.0) * modelMatrix;
    worldNormal = worldNorm;

    gl_Position = worldPos * viewProjectionMatrix;
}
