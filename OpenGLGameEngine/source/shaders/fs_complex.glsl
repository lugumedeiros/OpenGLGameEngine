#version 330 core

// IN
in vec3 defPos;
in vec3 defColor;
in vec2 defTexCoord;
in vec3 defNormal;

// VIEW
uniform vec3 viewPos;

// TEXTURE
uniform vec4 colorOverlay;
uniform float colorOverlayFactor;

uniform sampler2D baseTexture;
uniform float baseTexFactor;

uniform sampler2D overlayTexture;
uniform float overlayTexFactor;

// LIGHT
uniform vec3 ambientColor;

uniform vec3 sourceLightPos;
uniform vec3 sourceLightColor;

uniform float specularFactor;
uniform float shininess;

// OUT
out vec4 FragColor;

void main() {
	vec4 baseTexVec = texture( baseTexture, defTexCoord );
	vec4 OverTexVec = texture( overlayTexture, defTexCoord );

	FragColor = mix( vec4(defColor, 1.0), colorOverlay, colorOverlayFactor );
	FragColor = mix( FragColor, baseTexVec, baseTexFactor );
	FragColor = mix( FragColor, OverTexVec, overlayTexFactor );

	// LIGHT
	vec3 normalizedNormal = normalize(defNormal);
	vec3 lightDirection = normalize(sourceLightPos - defPos);
	float diffusion = max(dot(normalizedNormal, lightDirection), 0.0);

	vec3 viewDir = normalize(viewPos - defPos);
	vec3 reflectDir = reflect(-lightDirection, normalizedNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specularLight = specularFactor * spec * sourceLightColor;
	
	vec3 sumLight = (ambientColor) + (sourceLightColor * diffusion);
	vec3 finalColor = FragColor.rgb * sumLight + specularLight;

	// END FRAG
	FragColor = vec4(finalColor, FragColor.a);
}