#include "../../include/render/textureService.h"

TextureService::TextureService() {
	cache.insert({ "invalid_path", 0 });
}

GLuint TextureService::get(std::string_view texturePath) {
	std::string key(texturePath);

	if (cache.contains(key)) {
		return cache.at(key);
	}
	GLuint ID;
	bool success = createTexture(ID, texturePath);
	if (!success) {
		return 0;
	}
	cache.insert({ key, ID });
	std::cout << "TEXTURE '" << texturePath << "' WITH ID '" << ID << "' LOADED" << std::endl;
	return ID;
}

void TextureService::remove(std::string_view texturePath) {
	cache.erase(std::string{ texturePath });
}

bool TextureService::createTexture(GLuint& ID, std::string_view texturePath) {
	std::string path(texturePath);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: FAILED TO LOAD TEXTURE IMAGE '" << texturePath << "'" << std::endl;
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return true;
}
