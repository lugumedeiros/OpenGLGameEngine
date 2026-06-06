#include "../../include/render/textureService.h"

TextureService::TextureService() {
}

bool TextureService::loadAllTextures(std::string_view folderPath) {
	bool success = true;
	Texture* tex = nullptr;

	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		tex = loadTexture(entry.path().string());
		if (tex == nullptr) {
			return false;
		}
	}
	return true;
}

Texture* TextureService::getTexture(std::string_view textureName) {
	const auto& it = cache.find(std::string{ textureName });
	if (it != cache.end()) {
		return &it->second;
	}
	return nullptr;
}

Texture* TextureService::loadTexture(std::string_view texturePath) {
	GLuint ID = 0;
	std::filesystem::path path{ texturePath };
	if (std::filesystem::is_regular_file(path)) {
		std::string name{ path.filename().stem().string()};
		if (cache.contains(name)) {
			return &cache.at(name);
		}

		bool success = createGLTextureFromPath(ID, path);
		if (success) {
			cache.emplace( name, Texture{ ID, name, path });
			std::cout << "TEXTURE '" << name << "' WITH ID '" << ID << "' LOADED" << std::endl;
			return &cache.at(name);
		}
	}
	return nullptr;
}

void TextureService::removeTexture(std::string_view textureName) {
	Texture* tex = getTexture(textureName);
	if (tex == nullptr) {
		return;
	}
	glDeleteTextures(1, &tex->ID);
	cache.erase(std::string{ textureName });
}

std::vector<Texture*> TextureService::getAllTextures() {
	std::vector<Texture*> textures{};
	textures.reserve(cache.size());
	for (auto& [key, value] : cache) {
		textures.push_back(&value);
	}
	return textures;
}

bool TextureService::createGLTextureFromPath(GLuint& ID, const std::filesystem::path& texturePath) {
	std::string path{ texturePath.string() };

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: FAILED TO LOAD TEXTURE IMAGE '" << texturePath << "'" << std::endl;
		glDeleteTextures(1, &ID);
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return true;
}
