#ifndef BAPHOMET_GRAPHICS_H
#define BAPHOMET_GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* window_initialize(int width, int height, const char* title);
void window_terminate();
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* window_get_active_pointer();

#endif