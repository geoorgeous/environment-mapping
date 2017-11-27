#include "..\include\environment_map_scene.h"

EnvironmentMapScene::EnvironmentMapScene(const Window& window, CubeMap* skybox)
	: Scene(window, skybox) 
{
	m_cubemaps = {
		new CubeMap({ "res/textures/cubemaps/default/right.bmp",
		"res/textures/cubemaps/default/left.bmp",
		"res/textures/cubemaps/default/top.bmp",
		"res/textures/cubemaps/default/bottom.bmp",
		"res/textures/cubemaps/default/back.bmp",
		"res/textures/cubemaps/default/front.bmp" }),
		new CubeMap({ "res/textures/cubemaps/lake/right.jpg",
		"res/textures/cubemaps/lake/left.jpg",
		"res/textures/cubemaps/lake/top.jpg",
		"res/textures/cubemaps/lake/bottom.jpg",
		"res/textures/cubemaps/lake/back.jpg",
		"res/textures/cubemaps/lake/front.jpg" })
	};

	m_shaders = {
		new ShaderProgram("res/shaders/reflection.glsl"),
		new ShaderProgram("res/shaders/refraction.glsl")
	};

	m_meshes = {
		new Mesh("res/meshes/cube.obj"),
		new Mesh("res/meshes/sphere.obj"),
		new Mesh("res/meshes/teapot.obj")
	};

	m_currentMesh = 2;
	m_meshColour = glm::vec3(1.0f);
}

EnvironmentMapScene::~EnvironmentMapScene() 
{
	for (std::vector<CubeMap*>::iterator it = m_cubemaps.begin(); it != m_cubemaps.end(); ++it)
		delete (*it);
	m_cubemaps.clear();

	for (std::vector<ShaderProgram*>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
		delete (*it);
	m_shaders.clear();

	for (std::vector<Mesh*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		delete (*it);
	m_meshes.clear();
}

void EnvironmentMapScene::updateInput()
{
	Scene::updateInput();
}

void EnvironmentMapScene::render(ShaderProgram* shader)
{
	if (ImGui::CollapsingHeader("Environment"))
	{
		ImGui::Combo("##cubemap", &m_currentCubemap, "Default\0Lake");
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Shader"))
	{
		ImGui::RadioButton("Reflection", &m_currentShader, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Refraction", &m_currentShader, 1);

		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::Combo("##mesh", &m_currentMesh, "Cube\0Sphere\0Teapot");
		if (ImGui::TreeNode("Orientation"))
		{
			ImGui::Text("x");
			ImGui::SameLine();
			ImGui::DragFloat("##xx", &m_meshOrientation.x);
			ImGui::Text("y");
			ImGui::SameLine();
			ImGui::DragFloat("##yy", &m_meshOrientation.y);
			ImGui::Text("z");
			ImGui::SameLine();
			ImGui::DragFloat("##zz", &m_meshOrientation.z);

			ImGui::TreePop();
		}

		if (m_currentShader == 0)
		{
			if (ImGui::TreeNode("Colour"))
			{
				ImGui::ColorEdit3("##colour", &m_meshColour[0]);
				ImGui::TreePop();
			}
		}
		else if (m_currentShader == 1)
			ImGui::DragFloat("Refraction index", &m_refractionIndex, 0.0025f, 1.0f, 4.0f);

		ImGui::Separator();
	}

	m_skybox = m_cubemaps[m_currentCubemap];

	Scene::render(shader);

	m_shaders[m_currentShader]->enable();

	m_shaders[m_currentShader]->setUniform_mat4("view", &m_camera.getViewMatrix()[0][0]);
	m_shaders[m_currentShader]->setUniform_mat4("projection", &m_camera.getPerspectiveMatrix()[0][0]);
	m_shaders[m_currentShader]->setUniform_3f("eye", &m_camera.position()[0]);

	if (m_currentShader == 0)
		m_shaders[m_currentShader]->setUniform_3f("colour", &m_meshColour[0]);
	else if (m_currentShader == 1)
		m_shaders[m_currentShader]->setUniform_1f("c", m_refractionIndex);

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(m_meshOrientation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_meshOrientation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_meshOrientation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_meshes[m_currentMesh]->render(model, *shader);

	glUseProgram(0);
}