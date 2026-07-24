#version 330 core

struct Light {
	vec3 color;
	vec3 direction;
	vec3 pos;
};

struct Material {
	vec4 colorTint;
	float colorTintFactor;
	sampler2D albedo;
	float albedoFactor;
	sampler2D specular;
	float shininess;
};

struct Scene {
	Light ambient;
	Light source;
	Light directional;
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

//////////////////////////////////////////////////////////////////

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

// GLOBAL
vec3 normal = normalize(defNormal);

////////////////////////////////////////////////////////////////////

vec3 getSpecularLight(vec3 color, vec3 direction) {
	vec3 viewDirection = normalize(camera.pos - defPos);
	float mask = texture( material.specular, defTexCoord ).r;
	
	vec3 reflectionDirection = reflect(direction, normal);
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
	return mask * spec * color;
}

vec3 getDiffuseLight(vec3 color, vec3 direction) {
	float sourceDiffusion = max(dot(normal, -direction), 0.0);
	return color * sourceDiffusion;
}

////////////////////////////////////////////////////////////////////

void main() {
	// TEXTURE + TINT
	vec4 albedo = vec4( texture( material.albedo, defTexCoord ).rgb, 1.0f );
	FragColor = mix( vec4(defColor, 1.0), material.colorTint, material.colorTintFactor );
	FragColor = mix( FragColor, albedo, material.albedoFactor );

	// LIGHT - SPECULAR - DIRECTIONAL
	vec3 directionalSpecularLight = getSpecularLight( scene.directional.color, scene.directional.direction );

	// LIGHT - SPECULAR - SOURCE
	vec3 sourceLightDirection = normalize(scene.source.pos - defPos);
	vec3 sourceSpecularLight = getSpecularLight( scene.source.color, -sourceLightDirection );
	
	// LIGHT - DIFFUSION
	vec3 sourceDiffusion = getDiffuseLight(scene.source.color, -sourceLightDirection);
	vec3 directionalDiffusion = getDiffuseLight(scene.directional.color, scene.directional.direction);

	// LIGHT - SUM
	vec3 specularSum =  sourceSpecularLight + directionalSpecularLight;
	vec3 sumLight = (scene.ambient.color) + (sourceDiffusion) + (directionalDiffusion);
	vec3 finalColor = FragColor.rgb * sumLight + specularSum;

	// END FRAG
	FragColor = vec4(finalColor, FragColor.a);
}