#include "../../../include/engine/render/shaderCompiler.h"

ShaderProgram::ShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath) {
	std::string vertexSource = readShaderSource(vertexSourcePath);
	std::string fragmentSource = readShaderSource(fragmentSourcePath);
	if (vertexSource.empty() || fragmentSource.empty()) {
		success = false;
		return;
	}
	createShaderProgram(vertexSource, fragmentSource);
	if (!success) {
		std::cerr << "SHADER PROGRAM CREATION ABORTED" << std::endl;
		return;
	}

	loadUniforms(UNIFORM::CAMERA::names);
	loadUniforms(UNIFORM::OBJECT::names);
	loadUniforms(UNIFORM::MATERIAL::names);
	loadUniforms(UNIFORM::SCENE::names);
}

GLuint ShaderProgram::getID() const {
	return ID;
}

GLint ShaderProgram::getUniformID(std::string_view uniform) {
	auto it = uniformCache.find(std::string{ uniform });
	if (it != uniformCache.end()) {
		return it->second;
	}
	throw ("GET UNIFORM ID FAILED, ID NOT FOUND IN SHADER COMPILER CACHE");
}

GLuint ShaderProgram::compileShader(GLenum shaderType, std::string_view src) {
	std::string source(src);
	const char* srcCStr = source.c_str();
	
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &srcCStr, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		const char* type = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
		std::cerr << "ERROR: SHADER COMPILATION '" << type << "' FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

GLuint ShaderProgram::linkProgramShader(GLuint vertexShader, GLuint fragmentShader) {
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR: SHADER LINKING FAILED\n" << infoLog << std::endl;
	}
	return shaderProgram;
}

std::string ShaderProgram::readShaderSource(std::string_view sourcePath) {
	std::ifstream file(std::string{ sourcePath });
	if (!file.is_open()) {
		std::cerr << "ERROR: UNABLE TO READ SHADER FILE '" << sourcePath << "'" << std::endl;
		return "";
	}
	std::stringstream shaderStream;
	shaderStream << file.rdbuf();
	return shaderStream.str();
}

GLuint ShaderProgram::createShaderProgram(std::string_view vertexSource, std::string_view fragmentSource) {
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	if (!success) {
		return 0;
	}
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
	if (!success) {
		glDeleteShader(vertexShader);
		return 0;
	}
	std::cout << "SHADERS COMPILATION SUCCESS" << std::endl;

	GLuint shaderProgram = linkProgramShader(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (!success) {
		return 0;
	}
	std::cout << "SHADER PROGRAM LINKING SUCCESS" << std::endl;
	
	ID = shaderProgram;
	std::cout << "SHADER PROGRAM '" << ID << "' CREATED" << std::endl;
	return ID;
}

template <std::size_t N>
void ShaderProgram::loadUniforms(const std::array<std::string_view, N>& names) {
	for (std::string_view name : names) {
		std::string uniform{ name };
		GLint vertexLocation = glGetUniformLocation(ID, uniform.c_str());
		uniformCache.insert({ uniform, vertexLocation });
		if (vertexLocation < 0) {
			std::cout << "SHADER UNIFORM '" << name << "' NOT FOUND" << std::endl;
		}
	}
}
