#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

#include <array>
#include <glm.hpp>

class Frustum
{
public:
	enum side { FrustumPlane_Right = 0, FrustumPlane_Left, FrustumPlane_Top, FrustumPlane_Bottom, FrustumPlane_Far, FrustumPlane_Near };
	enum Plane { PLANE_BACK = 0, PLANE_FRONT, PLANE_RIGHT, PLANE_LEFT, PLANE_TOP, PLANE_BOTTOM };

	Frustum()
	{
		int wWidth, wHeight;
		glfwGetWindowSize(glfwGetCurrentContext(), &wWidth, &wHeight);
		m_aspect = (float)wWidth / (float)wHeight;

		m_projectionMatrix = glm::perspective(glm::radians(70.0f), m_aspect, 0.1f, 500.0f);
	}

	void CalculateFrustumPlanes(const glm::mat4& view)
	{
		const glm::mat4& v = view; //const glm::mat4& p = pojection;

		m_clipMatrix;

		m_clipMatrix[0][0] = v[0][0] * m_projectionMatrix[0][0] + v[0][1] * m_projectionMatrix[1][0] + v[0][2] * m_projectionMatrix[2][0] + v[0][3] * m_projectionMatrix[3][0];
		m_clipMatrix[1][0] = v[0][0] * m_projectionMatrix[0][1] + v[0][1] * m_projectionMatrix[1][1] + v[0][2] * m_projectionMatrix[2][1] + v[0][3] * m_projectionMatrix[3][1];
		m_clipMatrix[2][0] = v[0][0] * m_projectionMatrix[0][2] + v[0][1] * m_projectionMatrix[1][2] + v[0][2] * m_projectionMatrix[2][2] + v[0][3] * m_projectionMatrix[3][2];
		m_clipMatrix[3][0] = v[0][0] * m_projectionMatrix[0][3] + v[0][1] * m_projectionMatrix[1][3] + v[0][2] * m_projectionMatrix[2][3] + v[0][3] * m_projectionMatrix[3][3];
		m_clipMatrix[0][1] = v[1][0] * m_projectionMatrix[0][0] + v[1][1] * m_projectionMatrix[1][0] + v[1][2] * m_projectionMatrix[2][0] + v[1][3] * m_projectionMatrix[3][0];
		m_clipMatrix[1][1] = v[1][0] * m_projectionMatrix[0][1] + v[1][1] * m_projectionMatrix[1][1] + v[1][2] * m_projectionMatrix[2][1] + v[1][3] * m_projectionMatrix[3][1];
		m_clipMatrix[2][1] = v[1][0] * m_projectionMatrix[0][2] + v[1][1] * m_projectionMatrix[1][2] + v[1][2] * m_projectionMatrix[2][2] + v[1][3] * m_projectionMatrix[3][2];
		m_clipMatrix[3][1] = v[1][0] * m_projectionMatrix[0][3] + v[1][1] * m_projectionMatrix[1][3] + v[1][2] * m_projectionMatrix[2][3] + v[1][3] * m_projectionMatrix[3][3];
		m_clipMatrix[0][2] = v[2][0] * m_projectionMatrix[0][0] + v[2][1] * m_projectionMatrix[1][0] + v[2][2] * m_projectionMatrix[2][0] + v[2][3] * m_projectionMatrix[3][0];
		m_clipMatrix[1][2] = v[2][0] * m_projectionMatrix[0][1] + v[2][1] * m_projectionMatrix[1][1] + v[2][2] * m_projectionMatrix[2][1] + v[2][3] * m_projectionMatrix[3][1];
		m_clipMatrix[2][2] = v[2][0] * m_projectionMatrix[0][2] + v[2][1] * m_projectionMatrix[1][2] + v[2][2] * m_projectionMatrix[2][2] + v[2][3] * m_projectionMatrix[3][2];
		m_clipMatrix[3][2] = v[2][0] * m_projectionMatrix[0][3] + v[2][1] * m_projectionMatrix[1][3] + v[2][2] * m_projectionMatrix[2][3] + v[2][3] * m_projectionMatrix[3][3];
		m_clipMatrix[0][3] = v[3][0] * m_projectionMatrix[0][0] + v[3][1] * m_projectionMatrix[1][0] + v[3][2] * m_projectionMatrix[2][0] + v[3][3] * m_projectionMatrix[3][0];
		m_clipMatrix[1][3] = v[3][0] * m_projectionMatrix[0][1] + v[3][1] * m_projectionMatrix[1][1] + v[3][2] * m_projectionMatrix[2][1] + v[3][3] * m_projectionMatrix[3][1];
		m_clipMatrix[2][3] = v[3][0] * m_projectionMatrix[0][2] + v[3][1] * m_projectionMatrix[1][2] + v[3][2] * m_projectionMatrix[2][2] + v[3][3] * m_projectionMatrix[3][2];
		m_clipMatrix[3][3] = v[3][0] * m_projectionMatrix[0][3] + v[3][1] * m_projectionMatrix[1][3] + v[3][2] * m_projectionMatrix[2][3] + v[3][3] * m_projectionMatrix[3][3];

		m_planes[PLANE_RIGHT].x = m_clipMatrix[3][0] - m_clipMatrix[0][0];
		m_planes[PLANE_RIGHT].y = m_clipMatrix[3][1] - m_clipMatrix[0][1];
		m_planes[PLANE_RIGHT].z = m_clipMatrix[3][2] - m_clipMatrix[0][2];
		m_planes[PLANE_RIGHT].w = m_clipMatrix[3][3] - m_clipMatrix[0][3];

		m_planes[PLANE_LEFT].x = m_clipMatrix[3][0] + m_clipMatrix[0][0];
		m_planes[PLANE_LEFT].y = m_clipMatrix[3][1] + m_clipMatrix[0][1];
		m_planes[PLANE_LEFT].z = m_clipMatrix[3][2] + m_clipMatrix[0][2];
		m_planes[PLANE_LEFT].w = m_clipMatrix[3][3] + m_clipMatrix[0][3];

		m_planes[PLANE_BOTTOM].x = m_clipMatrix[3][0] + m_clipMatrix[1][0];
		m_planes[PLANE_BOTTOM].y = m_clipMatrix[3][1] + m_clipMatrix[1][1];
		m_planes[PLANE_BOTTOM].z = m_clipMatrix[3][2] + m_clipMatrix[1][2];
		m_planes[PLANE_BOTTOM].w = m_clipMatrix[3][3] + m_clipMatrix[1][3];

		m_planes[PLANE_TOP].x = m_clipMatrix[3][0] - m_clipMatrix[1][0];
		m_planes[PLANE_TOP].y = m_clipMatrix[3][1] - m_clipMatrix[1][1];
		m_planes[PLANE_TOP].z = m_clipMatrix[3][2] - m_clipMatrix[1][2];
		m_planes[PLANE_TOP].w = m_clipMatrix[3][3] - m_clipMatrix[1][3];

		m_planes[PLANE_BACK].x = m_clipMatrix[3][0] - m_clipMatrix[2][0];
		m_planes[PLANE_BACK].y = m_clipMatrix[3][1] - m_clipMatrix[2][1];
		m_planes[PLANE_BACK].z = m_clipMatrix[3][2] - m_clipMatrix[2][2];
		m_planes[PLANE_BACK].w = m_clipMatrix[3][3] - m_clipMatrix[2][3];

		m_planes[PLANE_FRONT].x = m_clipMatrix[3][0] + m_clipMatrix[2][0];
		m_planes[PLANE_FRONT].y = m_clipMatrix[3][1] + m_clipMatrix[2][1];
		m_planes[PLANE_FRONT].z = m_clipMatrix[3][2] + m_clipMatrix[2][2];
		m_planes[PLANE_FRONT].w = m_clipMatrix[3][3] + m_clipMatrix[2][3];

		for (int i = 0; i < 6; i++)
		{
			m_planes[i] = glm::normalize(m_planes[i]);
		}
	}

	bool PointInFrustum(glm::vec3 point)
	{
		for (int i = 0; i < 6; i++)
		{
			const float pos = m_planes[i].w;
			const glm::vec3 normal = glm::vec3(m_planes[i]);

			if (glm::dot(normal, point) + pos < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	bool SphereInFrustum(glm::vec3 point, float radius)
	{
		for (int i = 0; i < 6; i++)
		{
			const float& pos = m_planes[i].w;
			const glm::vec3& normal = glm::vec3(m_planes[i]);

			if (glm::dot(normal, point) + pos <= -glm::normalize(glm::vec4(point, radius)).w)
			{
				return false;
			}
		}

		return true;
	}
private:
	float m_aspect;
	glm::mat4 m_projectionMatrix, m_clipMatrix;
	std::array<glm::vec4, 6> m_planes;
};

#endif // !FRUSTUM_HPP