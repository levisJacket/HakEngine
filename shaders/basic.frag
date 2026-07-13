#version 330 core

in vec4 worldPosition;
in vec4 worldNormal;
in vec2 uvFrag;

struct PointLight{
    vec3 position;
    vec3 color;
    float radius;
    float intensity;
};

const int MAX_LIGHT = 4;
uniform PointLight u_Lights[MAX_LIGHT];

uniform sampler2D u_Texture;

out vec4 FragColor;

vec3 ACESFilm(vec3 x) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main()
{
    vec3 color = vec3(0.1, 0.1, 0.1);

    vec3 faceNormal = normalize(vec3(worldNormal));
    for(int i = 0;i < MAX_LIGHT ;i++){
	vec3 diff = u_Lights[i].position - vec3(worldPosition);
	float distance = length(diff);
	vec3 faceToLight = normalize(diff);
	float diffusion = max(dot(faceNormal, faceToLight), 0.0);

	float numerator = clamp(1.0 - pow(distance / u_Lights[i].radius, 4.0), 0.0, 1.0);
	float attenuation = (numerator * numerator) / (distance * distance + 0.0001);

	color = color + u_Lights[i].color * diffusion * attenuation * u_Lights[i].intensity;
    }

    color = ACESFilm(color);
    color = vec3(texture(u_Texture, uvFrag)) * color;

    FragColor = vec4(color, 1.0);
}
