#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 defPos;
out vec3 defColor;
out vec2 defTexCoord;
out vec3 defNormal;

void main(){

	// POS
	vec4 worldPos = uModel * vec4(aPos, 1.0f);
	gl_Position = uProjection * uView * worldPos;
	
	defPos = worldPos.xyz;
	defNormal = mat3(uModel) * aNormal;

	// TEXTURE
	defColor = aColor;
	defTexCoord = aTexCoord;

}