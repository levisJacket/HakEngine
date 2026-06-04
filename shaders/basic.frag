#version 330 core

in vec4 worldPosition;
in vec4 worldNormal;

struct PointLight{
    vec3 position;
    vec3 color;
};

const int MAX_LIGHT = 4;
uniform PointLight u_Lights[MAX_LIGHT];

out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.0, 0.0, 0.0);

    vec3 faceNormal = normalize(vec3(worldNormal));
    for(int i = 0;i < MAX_LIGHT ;i++){
	vec3 faceToLight = normalize(u_Lights[i].position - vec3(worldPosition));
	float a = dot(faceNormal, faceToLight);
	color = color + u_Lights[i].color * a;
    }

    FragColor = vec4(color, 1.0);
}
