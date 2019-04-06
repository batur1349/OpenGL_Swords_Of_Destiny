#include "../pch.h"
#include "Maths.hpp"


glm::mat4 Maths::CreateTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	// Create the matrix
	glm::mat4 transformationMatrix;

	// Translate the matrix
	transformationMatrix = glm::translate(transformationMatrix, translation);

	// Rotate the matrix
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale the matrix
	transformationMatrix = glm::scale(transformationMatrix, scale);

	// Return the matrix
	return transformationMatrix;
}

glm::mat4 Maths::CreateViewMatrix(Camera camera)
{
	// Create view matrix and set it to the identity matrix
	glm::mat4 viewMatrix = glm::mat4();

	// First rotate the cameras pitch
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	// Second rotate the cameras yaw
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

	// Third rotate the cameras roll
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.GetRoll()), glm::vec3(0.0f, 0.0f, 1.0f));

	// Get the camera position
	glm::vec3 cameraPosition = camera.GetPosition();

	// Translate the viewMatrix by opposite cameras position because if we want to move the world to the right
	// we have to move camera to the left.
	viewMatrix = glm::translate(viewMatrix, -cameraPosition);

	// Return the view matrix
	return viewMatrix;
}
