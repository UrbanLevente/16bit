#include <pch.h>
#include "Camera.h"



Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;

	if (height == 0) {
		height = 1;
	} else if (width == 0) {
		width = 1;
	}

	Position = position;

	// Start the camera focused and hide the cursor
	focused = true;  // Start the camera in focused mode
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Hide the cursor initially

}

void Camera::Matrix(GLFWwindow* window, float windowRatio, float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), windowRatio, 0.1f, 100.0f);

	glfwGetFramebufferSize(window, &width, &height);

	if (height == 0) {
		height = 1;
	} else if (width == 0) {
		width = 1;
	}

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);


	shader.SetUniformMat4f(uniform, projection * view);
}

void Camera::Inputs(GLFWwindow* window) {
	// Calculate deltaTime
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float adjustedSpeed = speed * deltaTime;

	// Toggles camera focus when pressing ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escPressed) {
		focused = !focused;
		escPressed = true;  // Prevents the key from toggling multiple times on a single press

		// Toggle cursor visibility when focus changes
		if (focused) {
			firstClick = true;  // Reset the firstClick flag so the cursor is centered when focusing again
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Hide the cursor and lock it
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // Show the cursor
		}
	} else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		escPressed = false;  // Allow toggle on next press
	}

	// If the camera is focused, handle movement and mouse inputs
	if (focused) {
		// Handles key inputs for movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Position += adjustedSpeed * Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			Position += adjustedSpeed * -glm::normalize(glm::cross(Orientation, Up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Position += adjustedSpeed * -Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			Position += adjustedSpeed * glm::normalize(glm::cross(Orientation, Up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			Position += adjustedSpeed * Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			Position += adjustedSpeed * -Up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed = 4.0f;
		} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			speed = 1.0f;
		}

		// Handle mouse inputs for camera rotation
		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));  // Center the cursor initially
			firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Prevent the camera from flipping upside down
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			Orientation = newOrientation;
		}

		// Rotate around the Up axis
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Reset cursor position to the center of the window
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
}
