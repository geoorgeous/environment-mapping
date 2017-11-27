#include "../include/scene.h"

Scene::Scene(const Window& renderWindow, CubeMap* skybox)
	: m_renderWindow(renderWindow), m_camera(glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.0f, 0.0f, -1.0f), 67.0f, renderWindow.getDimensions().x / renderWindow.getDimensions().y, 0.05f, 1000.0f), m_skybox(skybox) { }

Scene::~Scene() { }

void Scene::updateInput()
{
	if (m_renderWindow.isKeyDown(GLFW_KEY_W))
		m_camera.move(glm::vec3(0.0f, 0.0f, -1.0f));
	if (m_renderWindow.isKeyDown(GLFW_KEY_S))
		m_camera.move(glm::vec3(0.0f, 0.0f, 1.0f));
	if (m_renderWindow.isKeyDown(GLFW_KEY_A))
		m_camera.move(glm::vec3(-1.0f, 0.0f, 0.0f));
	if (m_renderWindow.isKeyDown(GLFW_KEY_D))
		m_camera.move(glm::vec3(1.0f, 0.0f, 0.0f));

	if (m_renderWindow.isKeyDown(GLFW_KEY_SPACE))
		m_camera.move(glm::vec3(0.0f, 1.0f, 0.0f));
	if (m_renderWindow.isKeyDown(GLFW_KEY_LEFT_CONTROL))
		m_camera.move(glm::vec3(0.0f, -1.0f, 0.0f));

	if (m_renderWindow.isKeyDown(GLFW_KEY_Q))
		m_camera.rotate(glm::vec3(0.0f, 0.0f, -3.0f));
	if (m_renderWindow.isKeyDown(GLFW_KEY_E))
		m_camera.rotate(glm::vec3(0.0f, 0.0f, 3.0f));

	glm::vec2 d = m_renderWindow.cursorPosDelta();
	if (d.x != 0 || d.y != 0)
	 m_camera.rotate(glm::vec3(0.0f, d.y, d.x));
}

void Scene::render(ShaderProgram* shader)
{
	m_skybox->render(m_camera.getViewMatrix(), m_camera.getPerspectiveMatrix());
}