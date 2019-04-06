#include "../pch.h"
#include "Camera.hpp"


Camera::Camera()
	: _cameraPosition(0.0f, 0.0f, 0.0f), _worldUP(0.0f, 1.0f, 0.0f), _cameraFront(0.0f, 0.0f, -1.0f)
{
	_pitch = 0.0f;
	_yaw = 0.0f;
	_roll = 0.0f;
}

void Camera::Update()
{
	static float movementSpeed = 0.2f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		_cameraPosition.z -= movementSpeed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		_cameraPosition.z += movementSpeed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		_cameraPosition.x -= movementSpeed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		_cameraPosition.x += movementSpeed;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
		_pitch--;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
		_pitch++;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
		_yaw--;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		_yaw++;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
		_roll--;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
		_roll++;
}
