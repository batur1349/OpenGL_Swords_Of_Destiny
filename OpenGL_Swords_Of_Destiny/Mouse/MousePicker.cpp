#include "../pch.h"
#include "MousePicker.hpp"


MousePicker::MousePicker(ThirdPersonCamera* camera, std::vector<Tile>* terrain)
	: _cameraPointer(camera), _terrainPointer(terrain)
{
	// Create the projection matrix
	int wWidth, wHeight;
	glfwGetWindowSize(glfwGetCurrentContext(), &wWidth, &wHeight);
	float aspect = (float)wWidth / (float)wHeight;
	_projectionMatrix = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 500.0f);

	_currentViewMatrix = _cameraPointer->GetViewMatrix();
}

void MousePicker::Update(const float& dt)
{
	if (_cameraPointer->GetViewMatrix() != _currentViewMatrix)
	{
		_currentViewMatrix = _cameraPointer->GetViewMatrix();
	}

	_currentRay = CalculateMouseRay();

	if (IntersectionInRange(0, RAY_RANGE, _currentRay))
	{
		_currentTerrainPoint = BinarySearch(0, 0, RAY_RANGE, _currentRay);

		if (!_clicked)
		{
			SetTerrain(_currentTerrainPoint.x, _currentTerrainPoint.z);
		}
	}
	else
	{
		_currentTerrainPoint = glm::vec3(0, 0, 0);
	}

	if (_clicked)
		_clickTime += dt;

	if (_clickTime >= _clickTimeMax)
	{
		_clicked = false;
		_clickTime = 0.0f;
	}
}

glm::vec3 MousePicker::CalculateMouseRay()
{
	static double mouseX, mouseY;
	glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);

	glm::vec2 normalizedCoords = GetNormalizedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
	glm::vec3 worldRay = ToWorldCoords(eyeCoords);

	return worldRay;
}

glm::vec2 MousePicker::GetNormalizedDeviceCoordinates(float mouseX, float mouseY)
{
	static int sizex, sizey;
	glfwGetWindowSize(glfwGetCurrentContext(), &sizex, &sizey);

	float x = (2.f * mouseX) / sizex - 1;
	float y = (2.f * mouseY) / sizey - 1;

	return glm::vec2(x, -y);
}

glm::vec4 MousePicker::ToEyeCoords(const glm::vec4& clipCoords)
{
	glm::mat4 invertedProjectionMatrix = Maths::InvertMatrix(_projectionMatrix);
	glm::vec4 eyeCoords = Maths::TransformMatrix(invertedProjectionMatrix, clipCoords);

	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.f);
}

glm::vec3 MousePicker::ToWorldCoords(const glm::vec4& eyeCoords)
{
	glm::mat4 invertedView = Maths::InvertMatrix(_cameraPointer->GetViewMatrix());
	glm::vec4 rayWorld = Maths::TransformMatrix(invertedView, eyeCoords);
	glm::vec3 mouseRay(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay);

	return mouseRay;
}

glm::vec3 MousePicker::GetPointOnRay(glm::vec3 ray, float distance)
{
	glm::vec3 camPos = _cameraPointer->GetPosition();
	glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
	glm::vec3 scaledRay(ray.x * distance, ray.y * distance, ray.z * distance);

	return glm::vec3(start.x + scaledRay.x, start.y + scaledRay.y, start.z + scaledRay.z);
}

glm::vec3 MousePicker::BinarySearch(int count, float start, float finish, glm::vec3 ray)
{
	float half = start + ((finish - start) / 2.f);

	if (count >= RECURSION_COUNT)
	{
		glm::vec3 endPoint = GetPointOnRay(ray, half);
		//Terrain* terrain = GetTerrain(endPoint.x, endPoint.z);
		//Terrain terrain = GetTerrain(endPoint.x, endPoint.z);

		return endPoint;
		//if (terrain != NULL)
		//{
		//	return endPoint;
		//}
		//else
		//{
		//	return glm::vec3(0, 0, 0);
		//}
	}

	if (IntersectionInRange(start, half, ray))
	{
		return BinarySearch(count + 1, start, half, ray);
	}
	else
	{
		return BinarySearch(count + 1, half, finish, ray);
	}
}

bool MousePicker::IntersectionInRange(float start, float finish, glm::vec3 ray)
{
	glm::vec3 startPoint = GetPointOnRay(ray, start);
	glm::vec3 endPoint = GetPointOnRay(ray, finish);

	//if (!IsUnderGround(startPoint) && IsUnderGround(endPoint))
	if (startPoint.y > 0 && endPoint.y < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MousePicker::SetTerrain(float worldX, float worldZ)
{
	for (int i = 0; i < _terrainPointer->size(); i++)
	{
		if (_terrainPointer->at(i).GetStartX() - 1.0f < worldX && _terrainPointer->at(i).GetEndX() - 1.0f > worldX &&
			_terrainPointer->at(i).GetStartZ() - 1.0f < worldZ && _terrainPointer->at(i).GetEndZ() - 1.0f > worldZ)
		{
			if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT))
			{
				if (_terrainPointer->at(i).GetSelected() == true)
					_terrainPointer->at(i).SetSelected(false);
				else
					_terrainPointer->at(i).SetSelected(true);

				_clicked = true;
			}
		}
	}
}