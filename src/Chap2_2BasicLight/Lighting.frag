#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 viewPos;


float specularStrength = 0.5f;
void main() {

    //漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float dif = max(dot(norm , lightDir) , 0.0f);
    vec3 diffuse = dif * lightColor;

    //环境光
    vec3 ambient = lightColor * ambientStrength;
    //镜面反射光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir , norm);
    float spec = pow(max(dot(viewDir , reflectDir) , 0.0f) , 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = objectColor * (ambient + diffuse + specular);
    FragColor = vec4(result , 1.0f);
}