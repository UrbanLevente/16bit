#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Camera {
public:

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Camera(int width, int height, glm::vec3 position);
	void Matrix(GLFWwindow* window, float windowRatio, float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);

private:
	int width;
	int height;
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 0.1f;
	float sensitivity = 100.0f;
	bool firstClick = true;

	// New variables
	bool escPressed = false;  // Tracks ESC press state
	bool focused = false;      // Tracks camera focus state
};
