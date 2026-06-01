#version 330 core

in vec3 normalFrag;
in mat4 moveNorm;

out vec4 FragColor;

void main()
{
    vec4 normal = vec4(normalFrag, 0) * moveNorm;
    float a = dot(vec3(normal.x, normal.y, normal.z ), vec3(0.0, 0.0, -1.0));
    FragColor = vec4(0, 0, a, 1.0);
}
