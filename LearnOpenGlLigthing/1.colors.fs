#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambinentStrength=0.1;
	vec3 ambient=ambinentStrength*lightColor;
	vec3 result=ambient*objectColor;
    FragColor = vec4(result, 1.0);
}