#ifndef MOUSEPICKER_HPP
#define MOUSEPICKER_HPP

#include "../Entity/ThirdPersonCamera.hpp"
#include "../Tile/Tile.hpp"
#include "../Maths/Maths.hpp"

class MousePicker
{
public:
	MousePicker(ThirdPersonCamera* camera, std::vector<Tile>* terrain);

	// Getters
	inline glm::vec3& GetCurrentRay() { return _currentRay; }
	inline glm::vec3& GetCurrentTerrainPoint() { return _currentTerrainPoint; }

	// Functions
	void Update(const float& dt);
private:
	// Variables
	glm::vec3 _currentRay;
	glm::mat4 _projectionMatrix, _currentViewMatrix;
	ThirdPersonCamera* _cameraPointer;
	const int RECURSION_COUNT = 100; //200
	const float RAY_RANGE = 100; // 600
	std::vector<Tile>* _terrainPointer;
	glm::vec3 _currentTerrainPoint;
	float _clickTimeMax = 0.1f, _clickTime = 0.0f;
	bool _clicked = false;

	// Functions
	glm::vec3 CalculateMouseRay();
	glm::vec2 GetNormalizedDeviceCoordinates(float mouseX, float mouseY);
	glm::vec4 ToEyeCoords(const glm::vec4& clipCoords);
	glm::vec3 ToWorldCoords(const glm::vec4& eyeCoords);

	glm::vec3 GetPointOnRay(glm::vec3 ray, float distance);
	glm::vec3 BinarySearch(int count, float start, float finish, glm::vec3 ray);
	bool IntersectionInRange(float start, float finish, glm::vec3 ray);
	void SetTerrain(float worldX, float worldZ);
};

#endif // !MOUSEPICKER_HPP