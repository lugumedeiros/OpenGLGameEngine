#version 330 core

struct Material {
	vec4 colorOverlay;
	float colorOverlayFactor;
	sampler2D baseTexture;
	float baseTexFactor;
	sampler2D overlayTexture;
	float overlayTexFactor;
};

struct Scene {
	vec3 ambientColor;
	vec3 sourceLightPos;
	vec3 sourceLightColor;
	float specularFactor;
	float shininess;
};

// IN
in vec3 defPos;
in vec3 defColor;
in vec2 defTexCoord;
in vec3 defNormal;

// UNIFORMS
uniform vec3 viewPos;
uniform Material material;
uniform Scene scene;

// OUT
out vec4 FragColor;

void main() {
	vec4 baseTexVec = texture( material.baseTexture, defTexCoord );
	vec4 overTexVec = texture( material.overlayTexture, defTexCoord );

	FragColor = mix( vec4(defColor, 1.0), material.colorOverlay, material.colorOverlayFactor );
	FragColor = mix( FragColor, baseTexVec, material.baseTexFactor );
	FragColor = mix( FragColor, overTexVec, material.overlayTexFactor );

	// LIGHT
	vec3 normalizedNormal = normalize(defNormal);
	vec3 lightDirection = normalize(scene.sourceLightPos - defPos);
	float diffusion = max(dot(normalizedNormal, lightDirection), 0.0);

	vec3 viewDir = normalize(viewPos - defPos);
	vec3 reflectDir = reflect(-lightDirection, normalizedNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), scene.shininess);
	vec3 specularLight = scene.specularFactor * spec * scene.sourceLightColor;
	
	vec3 sumLight = (scene.ambientColor) + (scene.sourceLightColor * diffusion);
	vec3 finalColor = FragColor.rgb * sumLight + specularLight;

	// END FRAG
	FragColor = vec4(finalColor, FragColor.a);
}