#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow* window_initialize(int width, int height, const char* title);
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif