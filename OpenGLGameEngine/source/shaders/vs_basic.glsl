#version 330 core

struct Camera {
	vec3 pos;
	mat4 projection;
	mat4 view;
};

struct Object {
	mat4 modelMatrix;
	mat3 normalMatrix;
};

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform Camera camera;
uniform Object object;

out vec3 defPos;
out vec3 defColor;
out vec2 defTexCoord;
out vec3 defNormal;

void main(){

	// POS
	vec4 worldPos = object.modelMatrix * vec4(aPos, 1.0f);
	gl_Position = camera.projection * camera.view * worldPos;
	
	defPos = worldPos.xyz;

	// TEXTURE
	defColor = aColor;
	defTexCoord = aTexCoord;

	// NORMAL
	defNormal = normalize(object.normalMatrix * aNormal);

}