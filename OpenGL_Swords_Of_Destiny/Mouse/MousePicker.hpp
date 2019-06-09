#ifndef MOUSEPICKER_HPP
#define MOUSEPICKER_HPP

#include "../Tile/Tile.hpp"
#include "../Maths/Maths.hpp"
#include "../Entity/Entity.hpp"

class MousePicker
{
public:
	MousePicker(ThirdPersonCamera* camera, std::vector<Tile>* terrain, std::vector<Entity>* entities,
		std::map<GLuint, std::pair<glm::vec3, glm::vec3>>* mapPtr);

	// Getters
	inline glm::vec3& GetCurrentRay() { return _currentRay; }
	inline glm::vec3& GetCurrentTerrainPoint() { return _currentTerrainPoint; }

	// Functions
	void Update(const float& dt);
private:
	// Variables
	glm::vec3 _currentRay, _currentTerrainPoint;
	glm::mat4 _projectionMatrix, _currentViewMatrix;
	ThirdPersonCamera* _cameraPointer;
	const int RECURSION_COUNT = 75; //200
	const float RAY_RANGE = 100; // 600
	std::vector<Tile>* _terrainPointer;
	std::vector<Entity>* _entitiesPointer;
	float _clickTimeMax = 0.2f, _clickTime = 0.0f, m_selectedTerrainIndex = 0.0f;
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
	std::map<GLuint, std::pair<glm::vec3, glm::vec3>>* _boundingBoxPtr;
};

#endif // !MOUSEPICKER_HPP