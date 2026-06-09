#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 defColor;
out vec2 defTexCoord;

void main(){
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
	defColor = aColor;
	defTexCoord = aTexCoord;
}