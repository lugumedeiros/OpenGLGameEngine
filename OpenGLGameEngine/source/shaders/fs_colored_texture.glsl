#version 330 core

in vec3 defColor;
in vec2 defTexCoord;

uniform sampler2D uniformTexture;
uniform vec4 uniformColor;

out vec4 FragColor;

void main() {
	vec4 textureColor = texture(uniformTexture, defTexCoord);
	FragColor = textureColor * uniformColor;
}