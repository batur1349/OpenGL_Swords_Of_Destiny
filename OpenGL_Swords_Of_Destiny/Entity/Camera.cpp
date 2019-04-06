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
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		_cameraPosition.z -= 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		_cameraPosition.z += 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		_cameraPosition.x -= 0.002f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		_cameraPosition.x += 0.002f;
}
