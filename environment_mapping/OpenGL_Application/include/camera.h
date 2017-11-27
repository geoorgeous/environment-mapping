#pragma once 


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


//! Stores the state of a camera.
/*! Stores all the information needed to control the way a given scene is displayed to the user. */
class Camera
{
public:
	//! Default constructor.
	/*! Creates a camera at (0,0,0), looking in the negative z direction, with a 67 degree FOV, a 1:1 aspect ratio, a near clip of 0.1, and a far clip of 100. */
	Camera();

	//! Primary Camera constructor.
	/*! @param position Pos.
	  * @param direction Direction.
	  * @param fov Fov.
	  * @param aspect Aspect.
	  * @param nearClip Nearclip.
	  * @param farClip Farclip. */
	Camera(glm::vec3 position, glm::vec3 direction, float fov, float aspect, float nearClip, float farClip);

	//! Camera object destructor.
	~Camera();

	//! Camera position.
	/*! @returns A reference to the Camera object's position containing its X, Y, and Z position. */
	const glm::vec3& position() const;

	//! Camera orientation around its own axis.
	/*! @returns A reference to the Camera object's orientation containing its X, Y, and Z orientations. */
	const glm::vec3& orientation() const;

	//! Gets a LookAt matrix constructed from the Camera's properties.
	/*! @returns A reference to the Camera's cached View matrix. */
	const glm::mat4& getViewMatrix() const;

	//! Gets a perspective projection matrix constructed from the Camera's properties.
	/*! @returns A reference to the Camera's cached erspective matrix. */
	const glm::mat4& getPerspectiveMatrix() const;

	//! Move the Camera object.
	/*! Moves the position of the camera along its own axis.
	  * @param offset The position offset.
	  * @note As this changes the position of the camera the View matrix is recalculated when calling @c move() */
	void move(glm::vec3 offset);

	//! Rotate the Camera object.
	/*! Rotates the orientation of the Camera.
	  * @param offset The amount of rotation to offset the current orientation by.
	  * @note As this changes the orientation of the camera the View matrix is recalculated when calling @c rotate() */
	void rotate(glm::vec3 offset);

private:
	float m_fov; /*!< Field of View (in degrees). */
	float m_aspect; /*!< Aspect ratio (width / height) */
	float m_nearClip; /*!< Distance from the camera that graphics will start being rendered. */
	float m_farClip; /*!< Distance from the camera that graphics will stop being rendered. */

	glm::mat4 m_matView; /*!< View matrix of the Camera object. */
	glm::mat4 m_matPerspective; /*!< Perspective projection matrix of the Camera object. */

	glm::vec3 m_position; /*< Camera position in 3D space. */
	glm::vec3 m_orientation; /*< Camera orientation in 3D space. */

	glm::vec3 m_up; /*!< The up-direction vector of the camera. Equivalant to its local Y axis. */;
	glm::vec3 m_forward; /*!< The forward-direction vector representing where the camera is pointed. Equivalant to its local Z axis. */;
	glm::vec3 m_right; /*!< The vector casting off to the right hand side of the camera. Equivalant to its local X axis. */

	float m_speed; /*! Camera movement speed modifier. */
	float m_rotationSensitivity; /*! Sensitivity to rotations. */

	//! Update the Camera's view matrix.
	/*! Recalculates and caches the View matrix with the Camera object's current position and orientation. This is generally called every time the Camera's position or orientation is changed. */
	void updateView();

	//! Update the Camera's perspective matrix.
	/*! Recalculates and caches the Perspective matrix with the Camera object's current field of view, aspect ratio, and clipping plane distances. */
	void updatePerspective();
};