#include "../../include/render/shaderCompiler.h"

bool ShaderCompiler::compileShader(unsigned int* shader, int shaderType, const char* src) {
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

bool ShaderCompiler::linkProgramShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int fragmentShader) {
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

GLuint ShaderCompiler::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
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
	
	programId = shaderProgram;
	std::cout << "SHADER PROGRAM '" << programId << "' CREATED" << std::endl;
	return programId;
}