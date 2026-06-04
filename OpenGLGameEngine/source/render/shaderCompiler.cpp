#include "../../include/render/shaderCompiler.h"

ShaderProgram::ShaderProgram(std::string_view vertexSourcePath, std::string_view fragmentSourcePath) {
	std::string vertexSource = readShaderSource(vertexSourcePath);
	std::string fragmentSource = readShaderSource(fragmentSourcePath);
	if (vertexSource.empty() || fragmentSource.empty()) {
		success = false;
		return;
	}
	createShaderProgram(vertexSource, fragmentSource);
}

void ShaderProgram::setUniformVec4(std::string_view name, const Vector4& vec) {
	uniformCache.insert_or_assign(std::string{ name }, vec);
}

void ShaderProgram::loadUniformCache() {
	int vertexLocation;
	for (const auto& [name, vec4] : uniformCache){
		vertexLocation = glGetUniformLocation(ID, name.c_str());
		glUniform4f(vertexLocation, vec4.x, vec4.y, vec4.z, vec4.w);
	}
}

GLuint ShaderProgram::getID() const {
	return ID;
}

bool ShaderProgram::compileShader(unsigned int* shader, int shaderType, std::string_view src) {
	std::string source(src);
	const char* srcCStr = source.c_str();
	
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, &srcCStr, NULL);
	glCompileShader(*shader);

	int success;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
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
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR: SHADER LINKING FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
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
