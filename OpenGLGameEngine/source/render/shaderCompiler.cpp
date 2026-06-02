#include "../../include/render/shaderCompiler.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
}

Vector4::Vector4(): x(0.5f), y(0.5f), z(0.5f), w(0.5f) {
}

bool ShaderProgram::compileShader(unsigned int* shader, int shaderType, const char* src) {
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, &src, NULL);
	glCompileShader(*shader);

	int success;
	char infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		const char* type = shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
		std::cerr << "ERROR: SHADER COMPILATION '" << type << "' FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool ShaderProgram::linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int fragmentShader) {
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		std::cerr << "ERROR: SHADER LINKING FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource) {
	createShaderProgram(vertexSource, fragmentSource);
}

GLuint ShaderProgram::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
	GLuint shaderProgram;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	success = compileShader(&vertexShader, GL_VERTEX_SHADER, vertexSource);
	if (!success) {
		return 0;
	}
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	success = compileShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentSource);
	if (!success) {
		return 0;
	}
	std::cout << "SHADERS COMPILATION SUCCESS" << std::endl;


	success = linkProgramShader(&shaderProgram, vertexShader, fragmentShader);
	if (!success) {
		return 0;
	}
	std::cout << "SHADER PROGRAM LINKING SUCCESS" << std::endl;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	ID = shaderProgram;
	std::cout << "SHADER PROGRAM '" << ID << "' CREATED" << std::endl;
	return ID;
}

void ShaderProgram::setVec4(std::string name, Vector4 vec) {
	uniformCache[name] = vec;
}

void ShaderProgram::loadUniformCache() {
	int vertexLocation;
	for (const auto& [name, vec4] : uniformCache){
		vertexLocation = glGetUniformLocation(ID, name.c_str());
		glUniform4f(vertexLocation, vec4.x, vec4.y, vec4.z, vec4.z);
	}
}
