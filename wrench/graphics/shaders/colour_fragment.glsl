#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 ambientLight;
uniform vec3 objectColour;

uniform vec3 lightPosition;
uniform vec3 lightColour;




void main(){

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    vec3 result = (ambientLight + diffuse) * objectColour;
    FragColor = vec4(result, 1.0);

}

