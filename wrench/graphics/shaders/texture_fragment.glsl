#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 ambientLight;

void main(){
    FragColor = vec4(ambientLight, 1.0) * (texture(ourTexture, TexCoord));
}

