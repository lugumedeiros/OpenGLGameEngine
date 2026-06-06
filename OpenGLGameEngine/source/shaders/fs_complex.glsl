#version 330 core

in vec3 defColor;
in vec2 defTexCoord;

uniform vec4 colorOverlay;
uniform float colorOverlayFactor;

uniform sampler2D baseTexture;
uniform float baseTexFactor;

uniform sampler2D overlayTexture;
uniform float overlayTexFactor;

out vec4 FragColor;

void main() {
	vec4 baseTexVec = texture(baseTexture, defTexCoord);
	vec4 OverTexVec = texture(overlayTexture, defTexCoord);

	FragColor = mix(vec4(defColor, 1.0), colorOverlay, colorOverlayFactor);
	FragColor = mix(FragColor, baseTexVec, baseTexFactor);
	FragColor = mix(FragColor, OverTexVec, overlayTexFactor);
}