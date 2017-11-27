
#define STB_IMAGE_IMPLEMENTATION
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define CLEAR_COLOUR 0.5f, 0.5f, 0.5f, 1.0f


#include <iostream>
#include <gl\glew.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>

#include "..\include\environment_map_scene.h"
#include "..\include\imgui_implementation.h"


bool init();
bool initGLFW();
bool initGLEW();
void loadAssets();


Window* mainWindow;
bool enableCameraMove = false;
int error = 0;


// Application entry point
int main()
{
	if (init())
	{
		if (enableCameraMove)
			mainWindow->disableCursor();

		loadAssets();

		/*CubeMap skybox({ "res/textures/cubemaps/lake/right.jpg",
			"res/textures/cubemaps/lake/left.jpg" ,
			"res/textures/cubemaps/lake/top.jpg" ,
			"res/textures/cubemaps/lake/bottom.jpg" ,
			"res/textures/cubemaps/lake/back.jpg" ,
			"res/textures/cubemaps/lake/front.jpg" });*/
		CubeMap skybox({ "res/textures/cubemaps/default/right.bmp",
			"res/textures/cubemaps/default/left.bmp" ,
			"res/textures/cubemaps/default/top.bmp" ,
			"res/textures/cubemaps/default/bottom.bmp" ,
			"res/textures/cubemaps/default/back.bmp" ,
			"res/textures/cubemaps/default/front.bmp" });
		EnvironmentMapScene scene(*mainWindow, &skybox);
		ShaderProgram shader("res/shaders/refraction.glsl");

		// GUI VARS
		int currentSelectedModel = 0;
		int currentSelectedSceneObject = 0;
		int currentTab = 0;

		while (!mainWindow->shouldClose())
		{
			glfwPollEvents();

			if (mainWindow->isKeyStroked(GLFW_KEY_ESCAPE))
				mainWindow->close();

			if (mainWindow->isKeyStroked(GLFW_KEY_M))
			{
				enableCameraMove = !enableCameraMove;

				if (mainWindow->isCursorDisabled())
					mainWindow->enableCursor();
				else
					mainWindow->disableCursor();
			}

			mainWindow->clear();

			ImGui::TextColored(ImVec4(1, 0, 0, 1), "%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			// Enable camera movement
			if (enableCameraMove)
				scene.updateInput();
			else
			{
				// Draw GUI
			}

			scene.render(&shader);

			mainWindow->swapBuffers();
		}
	}

	return error;
}



// Preforms all initialization
bool init()
{
	if (!initGLFW())
		return false;

	mainWindow = new Window((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, "FYP - 3D Scene Renderer", true);

	if (!initGLEW())
		return false;

	return true;
}



// Initialization logic for GLFW
bool initGLFW()
{
	if (!glfwInit())
	{
		error = 1;
		return false;
	}

	return true;
}



// Initialization for GLEW
bool initGLEW()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		error = 2;
		return false;
	}
	else
	{
		// Set a background color 
		glClearColor(CLEAR_COLOUR);

		// Tell OpenGL to cull back faces.
		glEnable(GL_CULL_FACE);

		// Tell OpenGL to only draw a pixel if its shape is closer to the viewer.
		// i.e. Enable depth testing with smaller depth value interpreted as being closer 
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	return true;
}



// Load in assets
void loadAssets()
{
}