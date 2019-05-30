#include "../pch.h"
#include "Maths.hpp"


glm::mat4 Maths::CreateTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
	// Create the matrix
	glm::mat4 matrix;

	// Translate the matrix
	matrix = glm::translate(matrix, translation);

	// Rotate the matrix
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale the matrix
	matrix = glm::scale(matrix, scale);

	// Return the matrix
	return matrix;
}

glm::mat4 Maths::CreateViewMatrix(ThirdPersonCamera& camera)
{
	//return glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetFront(), camera.GetWorldUP());
	glm::mat4 viewMatrix;

	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 cameraPos = camera.GetPosition();

	//viewMatrix = glm::translate(viewMatrix, -(cameraPos + camera.GetPlayerBodyGap()));

	viewMatrix = glm::translate(viewMatrix, -(cameraPos));

	return viewMatrix;
}

glm::mat4 Maths::InvertMatrix(const glm::mat4& matrix)
{
	float determinant = Determinant(matrix);

	if (determinant != 0)
	{
		/*
		* m00 m01 m02 m03
		* m10 m11 m12 m13
		* m20 m21 m22 m23
		* m30 m31 m32 m33
		*/

		float determinant_inv = 1.0f / determinant;

		// First row
		float t00 = Determinant3x3(matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3], matrix[3][1], matrix[3][2], matrix[3][3]);
		float t01 = -Determinant3x3(matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3], matrix[3][0], matrix[3][2], matrix[3][3]);
		float t02 = Determinant3x3(matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3], matrix[3][0], matrix[3][1], matrix[3][3]);
		float t03 = -Determinant3x3(matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2], matrix[3][0], matrix[3][1], matrix[3][2]);
		// second row
		float t10 = -Determinant3x3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[2][1], matrix[2][2], matrix[2][3], matrix[3][1], matrix[3][2], matrix[3][3]);
		float t11 = Determinant3x3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[2][0], matrix[2][2], matrix[2][3], matrix[3][0], matrix[3][2], matrix[3][3]);
		float t12 = -Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[2][0], matrix[2][1], matrix[2][3], matrix[3][0], matrix[3][1], matrix[3][3]);
		float t13 = Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[2][0], matrix[2][1], matrix[2][2], matrix[3][0], matrix[3][1], matrix[3][2]);
		// third row
		float t20 = Determinant3x3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][1], matrix[1][2], matrix[1][3], matrix[3][1], matrix[3][2], matrix[3][3]);
		float t21 = -Determinant3x3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[1][0], matrix[1][2], matrix[1][3], matrix[3][0], matrix[3][2], matrix[3][3]);
		float t22 = Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[1][0], matrix[1][1], matrix[1][3], matrix[3][0], matrix[3][1], matrix[3][3]);
		float t23 = -Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[1][0], matrix[1][1], matrix[1][2], matrix[3][0], matrix[3][1], matrix[3][2]);
		// fourth row
		float t30 = -Determinant3x3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3]);
		float t31 = Determinant3x3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3]);
		float t32 = -Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3]);
		float t33 = Determinant3x3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2]);

		// transpose and divide by the determinant
		glm::mat4 returnMatrix;
		returnMatrix[0][0] = t00 * determinant_inv;
		returnMatrix[1][1] = t11 * determinant_inv;
		returnMatrix[2][2] = t22 * determinant_inv;
		returnMatrix[3][3] = t33 * determinant_inv;
		returnMatrix[0][1] = t10 * determinant_inv;
		returnMatrix[1][0] = t01 * determinant_inv;
		returnMatrix[2][0] = t02 * determinant_inv;
		returnMatrix[0][2] = t20 * determinant_inv;
		returnMatrix[1][2] = t21 * determinant_inv;
		returnMatrix[2][1] = t12 * determinant_inv;
		returnMatrix[0][3] = t30 * determinant_inv;
		returnMatrix[3][0] = t03 * determinant_inv;
		returnMatrix[1][3] = t31 * determinant_inv;
		returnMatrix[3][1] = t13 * determinant_inv;
		returnMatrix[3][2] = t23 * determinant_inv;
		returnMatrix[2][3] = t32 * determinant_inv;

		return returnMatrix;
	}
	else
	{
		std::cerr << "Maths::InvertMatrix::Determinant is 0, returned IdentityMatrix" << std::endl;
		return glm::mat4();
	}
}

glm::vec4 Maths::TransformMatrix(const glm::mat4& matrix, const glm::vec4& vector)
{
	float x = matrix[0][0] * vector.x + matrix[1][0] * vector.y + matrix[2][0] * vector.z + matrix[3][0] * vector.w;
	float y = matrix[0][1] * vector.x + matrix[1][1] * vector.y + matrix[2][1] * vector.z + matrix[3][1] * vector.w;
	float z = matrix[0][2] * vector.x + matrix[1][2] * vector.y + matrix[2][2] * vector.z + matrix[3][2] * vector.w;
	float w = matrix[0][3] * vector.x + matrix[1][3] * vector.y + matrix[2][3] * vector.z + matrix[3][3] * vector.w;

	return glm::vec4(x, y, z, w);
}

float Maths::Determinant(const glm::mat4& matrix)
{
	float f =
		matrix[0][0]
		* ((matrix[1][1] * matrix[2][2] * matrix[3][3] + matrix[1][2] * matrix[2][3] * matrix[3][1] + matrix[1][3] * matrix[2][1] * matrix[3][2])
			- matrix[1][3] * matrix[2][2] * matrix[3][1]
			- matrix[1][1] * matrix[2][3] * matrix[3][2]
			- matrix[1][2] * matrix[2][1] * matrix[3][3]);
	f -= matrix[0][1]
		* ((matrix[1][0] * matrix[2][2] * matrix[3][3] + matrix[1][2] * matrix[2][3] * matrix[3][0] + matrix[1][3] * matrix[2][0] * matrix[3][2])
			- matrix[1][3] * matrix[2][2] * matrix[3][0]
			- matrix[1][0] * matrix[2][3] * matrix[3][2]
			- matrix[1][2] * matrix[2][0] * matrix[3][3]);
	f += matrix[0][2]
		* ((matrix[1][0] * matrix[2][1] * matrix[3][3] + matrix[1][1] * matrix[2][3] * matrix[3][0] + matrix[1][3] * matrix[2][0] * matrix[3][1])
			- matrix[1][3] * matrix[2][1] * matrix[3][0]
			- matrix[1][0] * matrix[2][3] * matrix[3][1]
			- matrix[1][1] * matrix[2][0] * matrix[3][3]);
	f -= matrix[0][3]
		* ((matrix[1][0] * matrix[2][1] * matrix[3][2] + matrix[1][1] * matrix[2][2] * matrix[3][0] + matrix[1][2] * matrix[2][0] * matrix[3][1])
			- matrix[1][2] * matrix[2][1] * matrix[3][0]
			- matrix[1][0] * matrix[2][2] * matrix[3][1]
			- matrix[1][1] * matrix[2][0] * matrix[3][2]);

	return f;
}

float Maths::Determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22)
{
	return t00 * (t11 * t22 - t12 * t21)
		+ t01 * (t12 * t20 - t10 * t22)
		+ t02 * (t10 * t21 - t11 * t20);
}
