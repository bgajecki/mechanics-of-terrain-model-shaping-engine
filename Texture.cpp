#include "Texture.hpp"

namespace engine
{
	Texture::Texture()
	{
		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	void Texture::bind(int index)
	{
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, this->id);
	}

	void Texture::load(const std::string& path)
	{
		// load and generate the texture
		int width, height, bpp;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 4);
		if (!data)
		{
			std::cerr << "Failed to load texture: " << path << std::endl;
			return;
		}

		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
}