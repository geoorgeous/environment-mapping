#pragma once


#include <string>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <stb\stb_image.h>


//! A wrapper class for using textures in OpenGL
class Texture
{
public:
	//! Create a Texture from an image file.
	/*! @param filepath The filepath of the Texture's image file. */
	Texture(const char* filepath);

	//! Default deconstructor.
	~Texture();

	//! Get the OpenGL texture ID.
	const GLuint& getID() const;

	//! Get the texture's dimensions.
	const glm::vec2& getSize() const;

	//! Bind the Texture to an OpenGL texture unit.
	/*! @param index The texture unit index to bind to. */
	void bind(unsigned int index) const;

	//! Unbind the Texture from the texture unit it is bound to.
	void unbind();

private:
	mutable GLuint m_textureUnitIndex = -1; /*!< The index of the OpenGL texture unit the Texture object is currently bound to. A value of -1 indicates the Texture is currently unbound. */
	GLuint m_id; /*!< The Texture's OpenGL texture ID. */
	glm::vec2 m_size; /*! Width and height of the texture's data. */

	//! Copy-prohibitting copy contructor.
	/*! @param texture The Texture object to copy from.
	  * @note This is made private so a Texture object cannot be copied. Texture object's should not be copied because they delete their OpenGL texture in their destructor. */
	Texture(const Texture& texture) = delete;

	//! Copy-prohibitting assignment operator.
	/*! @param texture The shader object to assign from.
	  * @note This is made private so Texture objects cannot be reassigned another Texture. */
	Texture& operator=(const Texture& texture) = delete;
};