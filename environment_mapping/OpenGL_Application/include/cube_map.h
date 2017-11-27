#pragma once


#include <string>
#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <stb\stb_image.h>

#include "shader_program.h"


//! A wrapper for an OpenGL cube map.
class CubeMap
{
public:
	CubeMap(std::vector<std::string> faceFilenames = {
		"res/textures/cubemaps/default/right.bmp",
		"res/textures/cubemaps/default/left.bmp",
		"res/textures/cubemaps/default/top.bmp",
		"res/textures/cubemaps/default/bottom.bmp",
		"res/textures/cubemaps/default/back.bmp",
		"res/textures/cubemaps/default/front.bmp" });

	~CubeMap();

	const int& id() const;

	void render(const glm::mat4& view, const glm::mat4& projection) const;

	//! Copy-prohibitting copy contructor.
	CubeMap(const CubeMap& texture) = delete;

	//! Copy-prohibitting assignment operator.
	CubeMap& operator=(const CubeMap& texture) = delete;

private:
	GLuint m_id;
	GLuint m_vao;
	GLuint m_vbo;
	ShaderProgram* m_shader;
};