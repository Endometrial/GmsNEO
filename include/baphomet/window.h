#ifndef BAPHOMET_WINDOW_H
#define BAPHOMET_WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define FBUF_CALLBACK_DIRECT_SCALE &_framebuffer_callback_direct_scale

#define DEFAULT_FBUF_CALLBACK FBUF_CALLBACK_DIRECT_SCALE

GLFWwindow* window_initialize(int width, int height, const char* title);
void window_terminate();
GLFWwindow* window_get_active_pointer();

void _framebuffer_callback_direct_scale(GLFWwindow* window, int width, int height);

#endif