#version 330 core

struct Material {
	vec4 colorOverlay;
	float colorOverlayFactor;
	sampler2D baseTexture;
	float baseTexFactor;
	sampler2D overlayTexture;
	float overlayTexFactor;
};

// IN
in vec3 defPos;
in vec3 defColor;
in vec2 defTexCoord;
in vec3 defNormal;

// UNIFORMS
uniform vec3 viewPos;
uniform Material material;

// OUT
out vec4 FragColor;

void main() {
	vec4 baseTexVec = texture( material.baseTexture, defTexCoord );
	vec4 overTexVec = texture( material.overlayTexture, defTexCoord );

	FragColor = mix( vec4(defColor, 1.0), material.colorOverlay, material.colorOverlayFactor );
	FragColor = mix( FragColor, baseTexVec, material.baseTexFactor );
	FragColor = mix( FragColor, overTexVec, material.overlayTexFactor );

}