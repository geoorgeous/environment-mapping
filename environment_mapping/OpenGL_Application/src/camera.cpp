#include "../include/camera.h"

Camera::Camera()
{
	m_fov = 67.0f;
	m_aspect = 1.0f;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;

	m_position = glm::vec3();
	m_orientation = glm::vec3();

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_right = cross(m_up, m_forward);

	m_speed = 0.1f;
	m_rotationSensitivity = 0.005f;

	updateView();
	updatePerspective();
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, float fov, float aspect, float nearClip, float farClip)
{
	m_fov = fov;
	m_aspect = aspect;
	m_nearClip = nearClip;
	m_farClip = farClip;

	m_position = position;
	m_orientation = glm::vec3();

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_forward = direction;
	m_right = cross(m_up, m_forward);

	m_speed = 0.1f;
	m_rotationSensitivity = 0.005f;

	updateView();
	updatePerspective();
}

Camera::~Camera() { }

const glm::vec3& Camera::position() const
{
	return m_position;
}

const glm::vec3& Camera::orientation() const
{
	return m_orientation;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return m_matView;
}

const glm::mat4& Camera::getPerspectiveMatrix() const
{
	return m_matPerspective;
}

void Camera::move(glm::vec3 offset)
{
	offset = (m_forward * offset.z) + (m_right * offset.x) + (m_up * offset.y);
	m_position += offset * m_speed;

	updateView();
}

void Camera::rotate(glm::vec3 offset)
{
	m_orientation += offset * m_rotationSensitivity;

	updateView();
}

void Camera::updateView()
{
	//roll can be removed from here. because is not actually used in FPS camera
	glm::mat4 matRoll = glm::mat4(1.0f);//identity matrix; 
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix

	//roll, pitch and yaw are used to store our angles in our class
	matRoll = glm::rotate(matRoll, m_orientation.x, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, m_orientation.y, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, m_orientation.z, glm::vec3(0.0f, 1.0f, 0.0f));

	//order matters
	glm::mat4 rotate = matRoll * matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, m_position);

	m_matView = rotate * translate;
}

void Camera::updatePerspective()
{
	m_matPerspective = glm::perspective(glm::radians(m_fov), m_aspect, m_nearClip, m_farClip);
}