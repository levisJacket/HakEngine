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
    vec4 worldPos = u_ModelMatrix * vec4(aPosition, 1.0); 
    worldPosition = worldPos;
    uvFrag = aUvFrag;

    vec4 worldNorm = u_ModelMatrix * vec4(aNormal, 0.0);
    worldNormal = worldNorm;

    gl_Position = u_ViewProjectionMatrix * worldPos;
}
