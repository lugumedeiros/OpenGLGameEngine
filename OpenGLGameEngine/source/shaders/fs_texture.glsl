#version 330 core

in vec3 defColor;
in vec2 defTexCoord;

uniform sampler2D uniformTexture;

out vec4 FragColor;

void main() {
	FragColor = texture(uniformTexture, defTexCoord);
}