#ifndef THIRDPERSONCAMERA_HPP
#define THIRDPERSONCAMERA_HPP

class ThirdPersonCamera
{
public:
	// Constructor
	ThirdPersonCamera();
	ThirdPersonCamera(glm::vec3* position, glm::vec3* rotation);
	// Destructor
	virtual ~ThirdPersonCamera();

	// Functions
	void Update(const float& dt);
	const glm::mat4& GetViewMatrix();

	// Getters
	inline const glm::vec3& GetPosition() { return m_position; }
	inline const float& GetPitch() { return m_pitch; }
	inline const float& GetYaw() { return m_yaw; }
	inline const float& GetRoll() { return m_roll; }
	inline const glm::vec3& GetWorldUP() { return m_worldUP; }

	static void Scroll_Callback(GLFWwindow* window, double x, double y);
private:
	// Variables
	bool m_pollygons;
	float m_angleAroundTheViewpoint, m_distanceFromViewpoint, m_pitch, m_yaw, m_roll, m_currentFBSpeed, m_currentRLSpeed;
	glm::vec3 m_position, m_worldUP, * m_viewpointPosition, * m_viewpointRotation;
	glm::mat4 m_viewMatrix;
	static int m_scrollY;
	double m_lastMouseX, m_lastMouseY;
	static constexpr float FB_SPEED = 20.0f, RL_SPEED = 20.0f, MAX_ZOOM_OUT = 40.0f, MAX_ZOOM_IN = 10.0f,
		MIN_PITCH = 10.0f, MAX_PITCH = 80.0f;

	// Functions
	void UpdateInput();
	void CalculateZoom();
	void CalculatePitch();
	void CalculateAngleAroundViewpoint();
	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();
	void CalculateCameraPosition(float horizontalDist, float verticalDist);
};

#endif // !THIRDPERSONCAMERA_HPP