#version 330 core

struct Material {
	vec4 colorTint;
	float colorTintFactor;
	sampler2D albedo;
	float albedoFactor;
	float specularFactor;
	float shininess;
};
struct Scene {
	vec3 ambientColor;
	vec3 sourceLightPos;
	vec3 sourceLightColor;
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
	vec4 albedo = texture( material.albedo, defTexCoord );
	FragColor = mix( vec4(defColor, 1.0), material.colorTint, material.colorTintFactor );
	FragColor = mix( FragColor, albedo, material.albedoFactor );

	// LIGHT
	vec3 normalizedNormal = normalize(defNormal);
	vec3 lightDirection = normalize(scene.sourceLightPos - defPos);
	float diffusion = max(dot(normalizedNormal, lightDirection), 0.0);

	vec3 viewDir = normalize(camera.pos - defPos);
	vec3 reflectDir = reflect(-lightDirection, normalizedNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specularLight = material.specularFactor * spec * scene.sourceLightColor;
	
	vec3 sumLight = (scene.ambientColor) + (scene.sourceLightColor * diffusion);
	vec3 finalColor = FragColor.rgb * sumLight + specularLight;

	// END FRAG
	FragColor = vec4(finalColor, FragColor.a);
}