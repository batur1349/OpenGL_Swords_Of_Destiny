#include "../pch.h"
#include "MousePicker.hpp"


MousePicker::MousePicker(ThirdPersonCamera* camera, std::vector<Tile>* terrain, std::vector<Entity>* entities,
	std::map<GLuint, std::pair<glm::vec3, glm::vec3>>* mapPtr)
	: _cameraPointer(camera), _terrainPointer(terrain), _entitiesPointer(entities), _boundingBoxPtr(mapPtr)
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

	UpdateSelections();

	UpdateClickTimer(dt);
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

bool MousePicker::TestEntities()
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	glm::vec3 invdir = 1.0f / _currentRay;
	static int sign[3];
	sign[0] = (invdir.x < 0);
	sign[1] = (invdir.y < 0);
	sign[2] = (invdir.z < 0);

	int selectedEntity = 999999;
	float globalxmin = 999999, globalzmin = 999999;
	for (int i = 0; i < _entitiesPointer->size(); i++)
	{
		float xmin = _entitiesPointer->at(i).GetPosition().x * (_currentRay.x);
		float zmin = _entitiesPointer->at(i).GetPosition().z * (_currentRay.z);

		tmin = (_entitiesPointer->at(i).GetBounds(sign[0]).x -
			_cameraPointer->GetPosition().x) * invdir.x;
		tmax = (_entitiesPointer->at(i).GetBounds(1 - sign[0]).x -
			_cameraPointer->GetPosition().x) * invdir.x;
		tymin = (_entitiesPointer->at(i).GetBounds(sign[1]).y -
			_cameraPointer->GetPosition().y) * invdir.y;
		tymax = (_entitiesPointer->at(i).GetBounds(1 - sign[1]).y -
			_cameraPointer->GetPosition().y) * invdir.y;

		if (!((tmin > tymax) || (tymin > tmax))) // No Collision
		{
			if (tymin > tmin)
				tmin = tymin;
			if (tymax < tmax)
				tmax = tymax;

			tzmin = (_entitiesPointer->at(i).GetBounds(sign[2]).z -
				_cameraPointer->GetPosition().z) * invdir.z;
			tzmax = (_entitiesPointer->at(i).GetBounds(1 - sign[2]).z -
				_cameraPointer->GetPosition().z) * invdir.z;

			if (!((tmin > tzmax) || (tzmin > tmax))) // No Collision
			{
				if (tzmin > tmin)
					tmin = tzmin;
				if (tzmax < tmax)
					tmax = tzmax;

				if (xmin < globalxmin && zmin < globalzmin)
				{
					globalxmin = xmin;
					globalzmin = zmin;

					selectedEntity = i;
				}
			}
		}
	}
	if (selectedEntity != 999999)
	{
		if (m_oldSelectedEntity != 999999)
			_entitiesPointer->at(m_oldSelectedEntity).SetSelected(false);

		if (m_oldSelectedTile != 999999)
			_terrainPointer->at(m_oldSelectedTile).SetSelected(false);

		m_oldSelectedEntity = selectedEntity;
		_entitiesPointer->at(selectedEntity).SetSelected(true);

		_clicked = true;
		return true;
	}
	else
	{
		if (m_oldSelectedEntity != 999999)
			_entitiesPointer->at(m_oldSelectedEntity).SetSelected(false);

		_clicked = true;
		return false;
	}
}

void MousePicker::TestTiles()
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	glm::vec3 invdir = 1.0f / _currentRay;
	static int sign[3];
	sign[0] = (invdir.x < 0);
	sign[1] = (invdir.y < 0);
	sign[2] = (invdir.z < 0);

	int selectedTile = 999999;
	for (int i = 0; i < _terrainPointer->size(); i++)
	{
		tmin = (_terrainPointer->at(i).GetBounds(sign[0]).x -
			_cameraPointer->GetPosition().x) * invdir.x;
		tmax = (_terrainPointer->at(i).GetBounds(1 - sign[0]).x -
			_cameraPointer->GetPosition().x) * invdir.x;
		tymin = (_terrainPointer->at(i).GetBounds(sign[1]).y -
			_cameraPointer->GetPosition().y) * invdir.y;
		tymax = (_terrainPointer->at(i).GetBounds(1 - sign[1]).y -
			_cameraPointer->GetPosition().y) * invdir.y;

		if (!((tmin > tymax) || (tymin > tmax))) //return; // No Collision
		{
			if (tymin > tmin)
				tmin = tymin;
			if (tymax < tmax)
				tmax = tymax;

			tzmin = (_terrainPointer->at(i).GetBounds(sign[2]).z -
				_cameraPointer->GetPosition().z) * invdir.z;
			tzmax = (_terrainPointer->at(i).GetBounds(1 - sign[2]).z -
				_cameraPointer->GetPosition().z) * invdir.z;

			if (!((tmin > tzmax) || (tzmin > tmax))) //return; // No Collision
			{
				if (tzmin > tmin)
					tmin = tzmin;
				if (tzmax < tmax)
					tmax = tzmax;

				selectedTile = i;
			}
		}
	}
	if (selectedTile != 999999)
	{
		if (!_terrainPointer->at(selectedTile).GetSelected())
		{
			if (m_oldSelectedTile != 999999)
				_terrainPointer->at(m_oldSelectedTile).SetSelected(false);

			_terrainPointer->at(selectedTile).SetSelected(true);
			m_oldSelectedTile = selectedTile;
		}
		else
			_terrainPointer->at(selectedTile).SetSelected(false);

		_clicked = true;
	}
	else
	{
		if (m_oldSelectedTile != 999999)
			_terrainPointer->at(m_oldSelectedTile).SetSelected(false);

		_clicked = true;
	}
}

void MousePicker::UpdateSelections()
{
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT) && !_clicked)
	{
		if (!TestEntities())
		{
			TestTiles();
		}
	}
	else if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) && !_clicked)
	{
		if (m_oldSelectedEntity != 999999)
			_entitiesPointer->at(m_oldSelectedEntity).SetSelected(false);

		if (m_oldSelectedTile != 999999)
			_terrainPointer->at(m_oldSelectedTile).SetSelected(false);
	}
}

void MousePicker::UpdateClickTimer(const float& dt)
{
	if (_clicked)
		_clickTime += dt;

	if (_clickTime >= _clickTimeMax)
	{
		_clicked = false;
		_clickTime = 0.0f;
	}
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

		return endPoint;
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
				if (!_terrainPointer->at(i).GetSelected())
				{
					_terrainPointer->at(m_selectedTerrainIndex).SetSelected(false);
					_terrainPointer->at(i).SetSelected(true);
					m_selectedTerrainIndex = i;
				}
				else
				{
					_terrainPointer->at(i).SetSelected(false);
				}

				_clicked = true;
			}
		}
	}
}