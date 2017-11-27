#pragma once


#include <string>

#include "camera.h"
#include "cube_map.h"
#include "shader_program.h"
#include "window.h"


//! Renderable scene.
class Scene
{
public:
	//! Create an empty Scene.
	Scene(const Window& renderWindow, CubeMap* cubeMap);

	//! Destructor.
	~Scene();

	//! Update the update for the scene's camera.
	virtual void updateInput() = 0;

	//! Render the scene in its entirety.
	/*! @param shader The ShaderProgram to render the scene's object's in. */
	virtual void render(ShaderProgram* shader) = 0;

protected:
	const Window& m_renderWindow; /*!< A reference to the Window object the scene renders on. */
	Camera m_camera; /*!< The camera which projects the scene. */
	CubeMap* m_skybox; /*!< The scene's environment skybox. */
};