#version 330 core

in vec4 worldPosition;
in vec4 worldNormal;

uniform vec3 lightLocation; 

out vec4 FragColor;

void main()
{

    vec3 faceToLight = normalize(vec3(worldPosition) - lightLocation);
    //vec3 faceToLight = normalize(lightLocation - vec3(worldPosition));
    vec3 faceNormal = normalize(vec3(worldNormal));
    float a = dot(faceNormal, faceToLight);

    FragColor = vec4(a, a, a, 1.0);
}
