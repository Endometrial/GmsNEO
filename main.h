#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine/media.h>
#include <engine/shader.h>
#include <engine/mesh.h>
#include <engine/draw.h>
#include <engine/math.h>
#include <engine/input.h>
#include <engine/graphics.h>

#define true 1
#define false 0

#define GLFW_VERSION_MAJOR 3
#define GLFW_VERSION_MINOR 3
#define GLFW_PROFILE GLFW_OPENGL_CORE_PROFILE

void endp(char* err);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* window_initialize(int width, int height, const char* title);

