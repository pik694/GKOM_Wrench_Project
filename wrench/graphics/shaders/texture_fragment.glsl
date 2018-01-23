#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 ambientLight;

uniform vec3 lightPosition;
uniform vec3 lightColour;

void main(){

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    FragColor = vec4(ambientLight + diffuse , 1.0) * (texture(ourTexture, TexCoord));
}

