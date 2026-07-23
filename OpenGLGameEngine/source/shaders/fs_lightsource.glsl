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
}
