#version 330 core

in vec3 defColor;
uniform vec4 colorOut;
out vec4 FragColor;

void main() {
	FragColor = vec4(defColor, 1.0);
}