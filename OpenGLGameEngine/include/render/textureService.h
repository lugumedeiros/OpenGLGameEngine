#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string_view>
#include <stb/stb_image.h>
#include <iostream>
#include <map>

class TextureService {
public:
	TextureService();
	GLuint get(std::string_view texturePath);
	void remove(std::string_view texturePath);

private:
	bool createTexture(GLuint& ID, std::string_view texturePath);
	std::map<std::string, GLuint> cache{};
};