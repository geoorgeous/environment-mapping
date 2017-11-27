#pragma once


#include <gl\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <imgui\imgui.h>

#include "imgui_implementation.h"


//! GLFWwindow wrapper-class.
/*! Wraps around GLFW functionality for creating and using windows. */
class Window
{
public:
	//! Default constructor
	Window();

	//! Constructs a Window with a specified width, height, and title.
	/*! @param width The width of the Window in pixels.
	  * @param height The height of the Window in pixels.
	  * @param title The title of the Window - this string appears at the top of the Window.
	  * @param makeCurrent If passed as true then the Window will immediately become the current OpenGL context upon creation. */
	Window(int width, int height, const char* title, bool makeCurrent = false);

	//! Default desctructor.
	/*! Destorys the GLFW window. */
	~Window();

	//! Check if the window got created.
	/*! @return True when GLFW fails to create the window. */
	bool created() const;

	//! Get the 2D dimensions of the window.
	/*! @return A 2D vector containing the width and height of the window as @p x and @p y components respectively. */
	const glm::vec2& getDimensions() const;

	//! Cursor position inside the Window.
	/*! @return The pixel X and Y position of the cursor relative to the top-left corner of ther Window context. */
	const glm::vec2& cursorPos() const;

	//! Cursor position delta.
	/*! @return The X and Y change in the cursor position since the last event poll. */
	const glm::vec2& cursorPosDelta() const;

	//! State of the window's cursor.
	/*! @return True if the cursor is disabled for this window. */
	const bool& isCursorDisabled() const;

	//! Disable the window's cursor. This hides the cursor's movement.
	void disableCursor();

	//! Enable the window's cursor.
	void enableCursor();

	//! Check if a key is pressed.
	/*! @param key Key enumeration of the key to check is down.
	  * @return True if the key is found to be pressed. */
	bool isKeyDown(int key) const;

	//! Check if a key is released after being pressed down.
	/*! @param key Key enumeration of the key to check is down.
	  * @return True if the key is found to have been released just after being pressed. */
	bool isKeyStroked(int key) const;

	//! Check if the Window should close.
	/*! @return Returns true when GLFW says this window should be closing. */
	bool shouldClose();

	//! Sets the window title.
	/*! @param title The string to set the Window's title to. */
	void setTitle(const char* title);

	//! Makes the Window the current OpenGL context.
	void makeCurrent();

	//! Set the Window to close.
	/*! Tells GLFW that this Window should be closing. */
	void close();

	//! Preforms pre-draw logic.
	void clear();

	//! Preforms post-draw logic.
	/*! Polls events and swaps the buffer. This should be called after drawing with OpenGL. */
	void swapBuffers();

private:
	bool m_isCreated = false; /*!< Flag for when GLFW fails to create a window. */
	glm::vec2 m_dimensions; /*! The 2D dimensions of the window. */
	GLFWwindow* m_window; /*!< GLFW window pointer. */
	glm::vec2 m_cursorPos; /*!< Cursor position relative to top left corner of window. */
	glm::vec2 m_cursorPosDelta; /*!< Change in cursor position. */
	bool m_disableCursor; /*!< Flag for hiding and disabled the cursor movement. */
	bool m_keysDownOld[GLFW_KEY_LAST]; /*!< Array of GLFW key states from old key state. */
	bool m_keysDownNew[GLFW_KEY_LAST]; /*!< Array of GLFW key states from latest key state. */

	//! GLFW callback function for when the cursor position changes.
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	//! GLFW callback function for when key states change.
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};