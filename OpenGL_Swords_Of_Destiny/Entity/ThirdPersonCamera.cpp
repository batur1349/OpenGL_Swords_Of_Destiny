#include "../pch.h"
#include "ThirdPersonCamera.hpp"

int ThirdPersonCamera::m_scrollY;

ThirdPersonCamera::ThirdPersonCamera()
{
	m_pollygons = false;
	m_worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
	m_viewpointPosition = new glm::vec3(0.0f, 0.0f, 0.0f);
	m_viewpointRotation = new glm::vec3(0.0f, 0.0f, 0.0f);

	m_pitch = 20.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scrollY = 0;

	m_distanceFromViewpoint = 20.0f;
	m_angleAroundTheViewpoint = 90.0f;

	m_currentFBSpeed = 0; m_currentRLSpeed = 0;

	SetCameraBounds();

	glfwSetScrollCallback(glfwGetCurrentContext(), Scroll_Callback);
}

ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, glm::vec3 rotation)
	: m_worldUP(0.0f, 1.0f, 0.0f)
{
	m_pollygons = false;

	//m_player = player;
	m_viewpointPosition = new glm::vec3(position);
	m_viewpointRotation = new glm::vec3(rotation);

	m_pitch = 20.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scrollY = 0;

	m_distanceFromViewpoint = 20.0f;
	m_angleAroundTheViewpoint = 90.0f;

	m_currentFBSpeed = 0; m_currentRLSpeed = 0;

	SetCameraBounds();

	glfwSetScrollCallback(glfwGetCurrentContext(), Scroll_Callback);
}

ThirdPersonCamera::~ThirdPersonCamera()
{
	//m_viewpointPosition = nullptr;
	delete m_viewpointPosition;
	//m_viewpointRotation = nullptr;
	delete m_viewpointRotation;
}

void ThirdPersonCamera::Update(const float& dt)
{
	// Update the Camera Input
	UpdateInput();

	// Calculate the Zoom Value
	CalculateZoom();

	// Calculate the Pitch Value (Vertical Movement of Camera)
	CalculatePitch();

	// Calculate the Angle Around Viewpoint
	CalculateAngleAroundViewpoint();

	float horizontalDistance = CalculateHorizontalDistance();
	float verticalDistance = CalculateVerticalDistance();

	CalculateCameraPosition(horizontalDistance, verticalDistance);

	// Calculate the Yaw Value
	m_yaw = 180.f - (m_viewpointRotation->y + m_angleAroundTheViewpoint);

	// Forward and Backward Operation
	float distance = m_currentFBSpeed * dt;
	float dx = distance * std::sin(glm::radians(m_viewpointRotation->y - m_yaw));
	float dz = distance * std::cos(glm::radians(m_viewpointRotation->y - m_yaw));

	// Right and Left Operation
	float distance2 = m_currentRLSpeed * dt;
	float dx2 = (distance2 * std::sin(glm::radians(m_viewpointRotation->y - m_yaw + 90.f))) * (-1);
	float dz2 = (distance2 * std::cos(glm::radians(m_viewpointRotation->y - m_yaw + 90.f))) * (-1);

	*m_viewpointPosition += glm::vec3(dx + dx2, 0.0f, dz + dz2);

	glfwGetCursorPos(glfwGetCurrentContext(), &m_lastMouseX, &m_lastMouseY);
}

const glm::mat4& ThirdPersonCamera::GetViewMatrix()
{
	// Reset the viewMatrix
	m_viewMatrix = glm::mat4(1.0f);

	// Rotate X Coordinate Based
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	// Rotate Y Coordinate Based
	m_viewMatrix = glm::rotate(m_viewMatrix, glm::radians(GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate the Camera Position
	m_viewMatrix = glm::translate(m_viewMatrix, -(GetPosition()));

	m_cameraUp = m_viewMatrix * glm::vec4(0, 1, 0, 0);
	m_cameraRight = m_viewMatrix * glm::vec4(1, 0, 0, 0);
	m_cameraFront = m_viewMatrix * glm::vec4(0, 0, -1, 0);

	return m_viewMatrix;
}

void ThirdPersonCamera::CalculateZoom()
{
	m_distanceFromViewpoint -= m_scrollY;

	if (m_distanceFromViewpoint < MAX_ZOOM_IN)
		m_distanceFromViewpoint = MAX_ZOOM_IN;
	else if (m_distanceFromViewpoint > MAX_ZOOM_OUT)
		m_distanceFromViewpoint = MAX_ZOOM_OUT;

	m_scrollY = 0;
}

void ThirdPersonCamera::CalculatePitch()
{
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		double posY;
		glfwGetCursorPos(glfwGetCurrentContext(), NULL, &posY);

		float pitchChange = posY - m_lastMouseY; pitchChange *= 0.2f;

		m_pitch += pitchChange;

		if (m_pitch < MIN_PITCH)
			m_pitch = MIN_PITCH;
		else if (m_pitch > MAX_PITCH)
			m_pitch = MAX_PITCH;
	}
}

void ThirdPersonCamera::CalculateAngleAroundViewpoint()
{
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		double posX;
		glfwGetCursorPos(glfwGetCurrentContext(), &posX, NULL);

		float angleChange = posX - m_lastMouseX; angleChange *= 0.5f;

		m_angleAroundTheViewpoint -= angleChange;
	}
}

float ThirdPersonCamera::CalculateHorizontalDistance()
{
	return m_distanceFromViewpoint * glm::cos(glm::radians(m_pitch));
}

float ThirdPersonCamera::CalculateVerticalDistance()
{
	return m_distanceFromViewpoint * glm::sin(glm::radians(m_pitch));
}

void ThirdPersonCamera::CalculateCameraPosition(float horizontalDist, float verticalDist)
{
	//float theta = m_player->GetRotation().y + m_angleAroundThePlayer;
	float theta = m_viewpointRotation->y + m_angleAroundTheViewpoint;

	float offsetX = horizontalDist * glm::sin(glm::radians(theta));
	float offsetZ = horizontalDist * glm::cos(glm::radians(theta));

	//m_position.x = m_player->GetPosition().x - offsetX;
	//m_position.y = m_player->GetPosition().y + verticalDist;
	//m_position.z = m_player->GetPosition().z - offsetZ;
	m_position.x = m_viewpointPosition->x - offsetX;
	m_position.y = m_viewpointPosition->y + verticalDist;
	m_position.z = m_viewpointPosition->z - offsetZ;

	// Check camera bounds
	if (m_viewpointPosition->x < m_cameraBoundXMin)
		m_viewpointPosition->x = m_cameraBoundXMin;
	else if (m_viewpointPosition->x > m_cameraBoundXMax)
		m_viewpointPosition->x = m_cameraBoundXMax;

	if (m_viewpointPosition->z < m_cameraBoundZMin)
		m_viewpointPosition->z = m_cameraBoundZMin;
	else if (m_viewpointPosition->z > m_cameraBoundZMax)
		m_viewpointPosition->z = m_cameraBoundZMax;
}

void ThirdPersonCamera::SetCameraBounds()
{
	m_cameraBoundXMin = -20.0f;
	m_cameraBoundXMax = 180.0f;
	m_cameraBoundZMin = -20.0f;
	m_cameraBoundZMax = 180.0f;
}

void ThirdPersonCamera::UpdateInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W))
	{
		m_currentFBSpeed = -FB_SPEED;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S))
	{
		m_currentFBSpeed = FB_SPEED;
	}
	else
	{
		m_currentFBSpeed = 0.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D))
	{
		m_currentRLSpeed = -RL_SPEED;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A))
	{
		m_currentRLSpeed = RL_SPEED;
	}
	else
	{
		m_currentRLSpeed = 0.0f;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R))
	{
		m_angleAroundTheViewpoint = 90.0f;
		m_pitch = 20.0f;
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F6))
	{
		if (m_pollygons)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_pollygons = false;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			m_pollygons = true;
		}
	}
}

void ThirdPersonCamera::Scroll_Callback(GLFWwindow* window, double x, double y)
{
	m_scrollY = y * 2;
}
