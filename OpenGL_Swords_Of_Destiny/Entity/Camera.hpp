#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
public:
	// Constructor
	Camera();
	// Functions
	void Update();
	// Getters
	inline glm::vec3 GetPosition() { return _cameraPosition; }
	inline float GetPitch() { return _pitch; }
	inline float GetYaw() { return _yaw; }
	inline float GetRoll() { return _roll; }

	inline glm::vec3 GetFront() { return _cameraFront; }
	inline glm::vec3 GetWorldUP() { return _worldUP; }
private:
	// Variables
	float _pitch, _yaw, _roll;
	glm::vec3 _cameraPosition, _worldUP, _cameraFront;
};

#endif // !CAMERA_HPP