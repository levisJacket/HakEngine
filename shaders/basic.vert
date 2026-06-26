#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUvFrag;

out vec4 worldPosition;
out vec4 worldNormal;
out vec2 uvFrag;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;

void main()
{
    vec4 worldPos = vec4(aPosition, 1.0) * u_ModelMatrix; 
    worldPosition = worldPos;
    uvFrag = aUvFrag;

    vec4 worldNorm = vec4(aNormal, 0.0) * u_ModelMatrix;
    worldNormal = worldNorm;

    gl_Position = worldPos * u_ViewProjectionMatrix;
}
