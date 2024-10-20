#pragma once

// std Lib
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

// OpenGL and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ImGui
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

// glm
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>