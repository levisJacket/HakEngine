#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    mat4 matProj = mat4 (
	vec4(0.66, 0.0, 0.0, 0.0),
	vec4(0.0, 1.0, 0.0, 0.0),
	vec4(0.0, 0.0, 1.0001, -0.10001),
	vec4(0.0, 0.0, 1.0, 0.0)
    );

    vec4 w = vec4(aPos, 1.0);
    gl_Position = matProj * w;

}
