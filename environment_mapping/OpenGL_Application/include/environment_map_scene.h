#pragma once


#include <vector>

#include "camera.h"
#include "cube_map.h"
#include "mesh.h"
#include "scene.h"
#include "shader_program.h"
#include "texture.h"
#include "window.h"


//! Renderable scene.
class EnvironmentMapScene : public Scene
{
public:
	//! Create an empty Scene.
	EnvironmentMapScene(const Window& renderWindow, CubeMap* skybox);

	//! Destructor.
	~EnvironmentMapScene();

	//! Update the update for the scene's camera.
	void updateInput() override;

	//! Render the scene in its entirety.
	/*! @param shader The ShaderProgram to render the scene's object's in. */
	void render(ShaderProgram* shader) override;

private:
	std::vector<CubeMap*> m_cubemaps;
	std::vector<ShaderProgram*> m_shaders;
	std::vector<Mesh*> m_meshes;

	int m_currentCubemap = 0;
	int m_currentShader = 0;
	int m_currentMesh = 0;
	float m_refractionIndex = 1.458;

	glm::vec3 m_meshOrientation;
	glm::vec3 m_meshColour;
};