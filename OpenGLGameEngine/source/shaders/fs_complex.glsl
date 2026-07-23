#version 330 core

struct Material {
	vec4 colorTint;
	float colorTintFactor;
	sampler2D albedo;
	float albedoFactor;
	sampler2D specular;
	float shininess;
};
struct Scene {
	vec3 ambientColor;
	vec3 sourceLightPos;
	vec3 sourceLightColor;
	vec3 directionalLightColor;
	vec3 directionalLightDirection;
};
struct Camera {
	vec3 pos;
	mat4 projection;
	mat4 view;
};
struct Object {
	mat4 modelMatrix;
	mat3 normalMatrix;
};

// IN
in vec3 defPos;
in vec3 defColor;
in vec2 defTexCoord;
in vec3 defNormal;

// UNIFORMS
uniform Camera camera;
uniform Material material;
uniform Scene scene;

// OUT
out vec4 FragColor;

void main() {
	// TEXTURE + TINT
	vec4 albedo = vec4( texture( material.albedo, defTexCoord ).rgb, 1.0f );
	FragColor = mix( vec4(defColor, 1.0), material.colorTint, material.colorTintFactor );
	FragColor = mix( FragColor, albedo, material.albedoFactor );

	// LIGHT
	vec3 normalizedNormal = normalize(defNormal);
	vec3 viewDir = normalize(camera.pos - defPos);
	float specMask = texture( material.specular, defTexCoord ).r;

	// LIGHT - SPECULAR - DIRECTIONAL
	vec3 directionalReflectDir = reflect(scene.directionalLightDirection, normalizedNormal);
	float directionalSpecDir = pow(max(dot(viewDir, directionalReflectDir), 0.0), material.shininess);
	vec3 directionalSpecularLight = specMask * directionalSpecDir * scene.directionalLightColor;

	// LIGHT - SPECULAR - SOURCE
	vec3 sourceLightDirection = normalize(scene.sourceLightPos - defPos);
	vec3 sourceReflectDir = reflect(-sourceLightDirection, normalizedNormal);
	float sourceSpecDir = pow(max(dot(viewDir, sourceReflectDir), 0.0), material.shininess);
	vec3 sourceSpecularLight = specMask * sourceSpecDir * scene.sourceLightColor;
	
	// LIGHT - DIFFUSION
	float sourceDiffusion = max(dot(normalizedNormal, sourceLightDirection), 0.0);
	float directionalDiffusion = max(dot(normalizedNormal, -scene.directionalLightDirection), 0.0); 

	// LIGHT - SUM
	vec3 specularSum =  sourceSpecularLight + directionalSpecularLight;
	vec3 sumLight = (scene.ambientColor) + (scene.sourceLightColor * sourceDiffusion) + (scene.directionalLightColor * directionalDiffusion);
	vec3 finalColor = FragColor.rgb * sumLight + specularSum;

	// END FRAG
	FragColor = vec4(finalColor, FragColor.a);
}