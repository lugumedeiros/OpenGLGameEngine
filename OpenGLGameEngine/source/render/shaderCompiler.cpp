#include "../../include/render/shaderCompiler.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
}

Vector4::Vector4(): x(0.5f), y(0.5f), z(0.5f), w(0.5f) {
}


ShaderProgram::ShaderProgram(const std::string& vertexSourcePath, const std::string& fragmentSourcePath) {
	std::string vertexSource = readShaderSource(vertexSourcePath);
	std::string fragmentSource = readShaderSource(fragmentSourcePath);
	if (vertexSource.empty() || fragmentSource.empty()) {
		success = false;
		return;
	}
	createShaderProgram(vertexSource, fragmentSource);
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

std::string ShaderProgram::readShaderSource(const std::string& sourcePath) {
	std::ifstream file(sourcePath);
	if (!file.is_open()) {
		std::cerr << "ERROR: UNABLE TO READ SHADER FILE '" << sourcePath << "'" << std::endl;
		return "";
	}
	std::stringstream shaderStream;
	shaderStream << file.rdbuf();
	return shaderStream.str();
}

GLuint ShaderProgram::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
	GLuint shaderProgram;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	success = compileShader(&vertexShader, GL_VERTEX_SHADER, vertexSource.c_str());
	if (!success) {
		return 0;
	}
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	success = compileShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentSource.c_str());
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
