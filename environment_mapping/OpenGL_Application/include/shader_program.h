#pragma once


#include <fstream>
#include <gl\glew.h>
#include <sstream>
#include <string>
#include <vector>

#include "shader.h"


//! Wrapper class for OpenGL shader programs.
/*! Wraps up creation, destruction, and general functionality of an OpenGL shader program. */
class ShaderProgram
{
public:
	//! Create an OpenGL shader program from a GLSL file.
	/*! @param filepath Filepath of the GLSL file containing one or more Shader's source code. */
	ShaderProgram(const char* filepath);

	//! Shader destructor which frees OpenGL Shader program.
	~ShaderProgram();

	//! Get's the Shader object's OpenGL ID. 
	/*! @return OpenGL ID for the shader program. */
	GLuint getID() const;

	//! Get's the location of a uniform. 
	/*! @param uniformName The name of the uniform to fetch the location of.
	  * @return GLuint representing the location of the uniform. Returns -1 if the uniform does not exist. */
	GLuint getUniformLoc(const char* uniformName) const;

	//! Sets an integer uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param i The value to pass to the uniform. */
	void setUniform_1i(const char* uniformName, const GLint i) const;

	//! Sets a float uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param f The value to pass to the uniform. */
	void setUniform_1f(const char* uniformName, const GLfloat f) const;

	//! Sets a vec2 uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param f The value to pass to the uniform. */
	void setUniform_2f(const char* uniformName, const GLfloat f[2]) const;

	//! Sets a vec3 uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param f The value to pass to the uniform. */
	void setUniform_3f(const char* uniformName, const GLfloat f[3]) const;

	//! Sets a vec4 uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param f The value to pass to the uniform. */
	void setUniform_4f(const char* uniformName, const GLfloat f[4]) const;

	//! Sets a mat4 uniform's value.
	/*! @param uniformName The name of the uniform to set.
	  * @param m The value to pass to the uniform. */
	void setUniform_mat4(const char* uniformName, const GLfloat m[16]) const;

	//! Enable the OpenGL shader.
	void enable() const;

	//! Check to see if program linked.
	/*! @return True if the OpenGL program linked successfully upon creation of the ShaderProgram object. */
	bool linked() const;

private:
	GLuint m_id; /*!< The shader program ID OpenGL stores. */

	//! Copy-prohibitting copy contructor.
	/*! @param shaderProgram The ShaderProgram object to copy from.
	  * @note This is made private so a ShaderProgram object cannot be copied. ShaderProgram object's should not be copied because they delete their OpenGL program in their destructor. */
	ShaderProgram(const ShaderProgram& shaderProgram) = delete;

	//! Copy-prohibitting assignment operator.
	/*! @param shaderProgram The ShaderProgram object to assign from.
	  * @note This is made private so ShaderProgram objects cannot be reassigned another ShaderProgram. */
	ShaderProgram& operator=(const ShaderProgram& shaderProgram) = delete;

	//! Attach a Shader to the ShaderProgram
	/*! @param shader The Shader object to attach to the program. */
	void attachShader(const Shader* shader) const;

	//! Attempts to link the OpenGL shader program.
	void link() const;
};