#include "../include/texture.h"

Texture::Texture(const char* filepath)
{
	glGenTextures(1, &m_id);
	bind(0);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		m_size = glm::vec2(width, height);
	}

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

const GLuint& Texture::getID() const
{
	return m_id;
}

const glm::vec2& Texture::getSize() const
{
	return m_size;
}

void Texture::bind(unsigned int index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, m_id);

	m_textureUnitIndex = index;
}

void Texture::unbind()
{
	if (m_textureUnitIndex > -1)
	{
		glActiveTexture(GL_TEXTURE0 + m_textureUnitIndex);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureUnitIndex = -1;
	}
}