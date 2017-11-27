#include "../include/window.h"

Window::Window() { }

Window::Window(int width, int height, const char* title, bool makeCurrent)
	: m_dimensions(width, height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (m_window)
	{
		if (makeCurrent)
			this->makeCurrent();

		ImGui_ImplGlfwGL3_Init(m_window, true); ImGui::GetIO().IniFilename = "res/config/imgui.ini";

		glfwSetKeyCallback(m_window, Window::key_callback);
		glfwSetCursorPosCallback(m_window, Window::cursor_position_callback);

		glfwSetWindowUserPointer(m_window, this);

		m_isCreated = true;
	}
}

Window::~Window()
{
	ImGui_ImplGlfwGL3_Shutdown();
	glfwDestroyWindow(m_window);
}

bool Window::created() const
{
	return m_isCreated;
}

const glm::vec2& Window::getDimensions() const
{
	return m_dimensions;
}

const glm::vec2& Window::cursorPos() const
{
	return m_cursorPos;
}

const glm::vec2& Window::cursorPosDelta() const
{
	return m_cursorPosDelta;
}

const bool& Window::isCursorDisabled() const
{
	return glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Window::disableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::enableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPos(m_window, m_dimensions.x / 2, m_dimensions.y / 2);
}

bool Window::isKeyDown(int key) const
{
	return m_keysDownNew[key];
}

bool Window::isKeyStroked(int key) const
{
	return m_keysDownOld[key] && !m_keysDownNew[key];
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window) != 0;
}

void Window::setTitle(const char* title)
{
	glfwSetWindowTitle(m_window, title);
}

void Window::makeCurrent()
{
	glfwMakeContextCurrent(m_window);
}

void Window::close()
{
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplGlfwGL3_NewFrame();
}

void Window::swapBuffers()
{
	ImGui::Render();

	glfwSwapBuffers(m_window);

	m_cursorPosDelta = glm::vec2();

	memcpy(m_keysDownOld, m_keysDownNew, sizeof(m_keysDownNew));
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	glm::vec2 newPos((float)x, (float)y);

	Window* thisWindow = (Window*)glfwGetWindowUserPointer(window);

	thisWindow->m_cursorPosDelta = newPos - thisWindow->m_cursorPos;
	thisWindow->m_cursorPos = newPos;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* thisWindow = (Window*)glfwGetWindowUserPointer(window);

	thisWindow->m_keysDownOld[key] = thisWindow->m_keysDownNew[key];

	if (action == GLFW_RELEASE) thisWindow->m_keysDownNew[key] = false;
	else if (action == GLFW_PRESS) thisWindow->m_keysDownNew[key] = true;

	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
}