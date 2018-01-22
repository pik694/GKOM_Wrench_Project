#version 330 core

in vec3 Normal;

out vec4 FragColor;

uniform vec3 ambientLight;
uniform vec3 objectColour;

void main(){

    vec3 result = ambientLight * objectColour;

    FragColor = vec4(result, 1.0);

}

