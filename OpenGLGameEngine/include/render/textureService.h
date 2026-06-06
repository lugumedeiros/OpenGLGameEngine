#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string_view>
#include <stb/stb_image.h>
#include <iostream>
#include <filesystem>
#include <map>
#include <unordered_set>
#include <vector>

class Texture {
public:
	Texture(GLuint ID, std::string_view name, std::filesystem::path path)
		: ID(ID), name(name), path(path)  {
	}
	GLuint ID{0};
	std::string name{};
	std::filesystem::path path{};
};

class TextureService {
public:
	TextureService();
	bool loadAllTextures(std::string_view folderPath);
	Texture* loadTexture(std::string_view texturePath);
	Texture* getTexture(std::string_view textureName);
	void removeTexture(std::string_view textureName);
	std::vector<Texture*> getAllTextures();

private:
	bool createGLTextureFromPath(GLuint& ID, const std::filesystem::path& texturePath);
	std::map<std::string, Texture> cache{};
};