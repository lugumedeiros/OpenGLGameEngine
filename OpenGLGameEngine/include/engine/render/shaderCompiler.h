#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <array>

struct UNIFORM {
	struct CAMERA {
		static constexpr std::string_view PROJECTION = "camera.projection";
		static constexpr std::string_view POSITION = "camera.pos";
		static constexpr std::string_view VIEW = "camera.view";
		static constexpr std::array names{PROJECTION, POSITION, VIEW};
	};
	struct OBJECT {
		static constexpr std::string_view MODEL_MATRIX = "object.modelMatrix";
		static constexpr std::string_view NORMAL_MATRIX = "object.normalMatrix";
		static constexpr std::array names{ MODEL_MATRIX, NORMAL_MATRIX };
	};
	struct MATERIAL {
		static constexpr std::string_view ALBEDO = "material.albedo";
		static constexpr std::string_view ALBEDO_FACTOR = "material.albedoFactor";
		static constexpr std::string_view COLOR_TINT = "material.colorTint";
		static constexpr std::string_view COLOR_TINT_FACTOR = "material.colorTintFactor";
		static constexpr std::string_view SPECULAR_FACTOR = "material.specularFactor";
		static constexpr std::string_view SHININESS = "material.shininess";
		static constexpr std::array names{ ALBEDO, ALBEDO_FACTOR, COLOR_TINT, COLOR_TINT_FACTOR, SPECULAR_FACTOR, SHININESS };

	};
	struct SCENE {
		static constexpr std::string_view AMBIENT_COLOR = "scene.ambientColor";
		static constexpr std::string_view SOURCE_LIGHT_POS = "scene.sourceLightPos";
		static constexpr std::string_view SOURCE_LIGHT_COLOR = "scene.sourceLightColor";
		static constexpr std::array names{ AMBIENT_COLOR, SOURCE_LIGHT_POS, SOURCE_LIGHT_COLOR };
	};
};


class ShaderProgram {
public:
	ShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath);
	
	int success{false};

	GLuint getID() const;
	GLint getUniformID(std::string_view uniform);

private:
	GLuint ID{ 0 };
	std::string readShaderSource(std::string_view sourcePath);
	GLuint createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource);
	GLuint compileShader(GLenum shaderType, std::string_view src);
	GLuint linkProgramShader(GLuint vertexShader, GLuint FragmentShader);

	template <std::size_t N>
	void loadUniforms(const std::array<std::string_view, N>& names);
	
	std::map<std::string, GLint> uniformCache;
};
