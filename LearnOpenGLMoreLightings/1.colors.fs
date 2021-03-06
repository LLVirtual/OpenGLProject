#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
  
//创建struct
struct Material {
	sampler2D diffuseTex;
    sampler2D specular;
    float shininess;
}; 
uniform Material material;
in vec2 Texcoords;

struct Light {
    vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

uniform Light light;
uniform vec3 viewPos;
void main()
{    
    // 环境光
    //vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = light.ambient  * vec3(texture(material.diffuseTex,Texcoords));
    // 漫反射 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position- FragPos);
	//vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuseTex,Texcoords)));

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular,Texcoords)));  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}