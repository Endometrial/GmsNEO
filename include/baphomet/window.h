#ifndef BAPHOMET_WINDOW_H
#define BAPHOMET_WINDOW_H

/*
	Window.h
	Created: xxxx-xx-xx
	Description:
		Window.h is a going through something of
		a mid-life crisis as i decide whether it should
		wrap window functionality only or project initialization
		functionality as well.
*/

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define FBUF_CALLBACK_DIRECT_SCALE &_framebuffer_callback_direct_scale
#define CLOSE_CALLBACK_DEFAULT &_window_close_callback

#define DEFAULT_FBUF_CALLBACK FBUF_CALLBACK_DIRECT_SCALE
#define DEFAULT_CLOSE_CALLBACK CLOSE_CALLBACK_DEFAULT



typedef GLFWwindow Window;

Window* window_create(int width, int height, const char* title);
void window_destroy(Window* window);
Window* window_get_active();
void window_set_active(Window* window);

void _framebuffer_callback_direct_scale(GLFWwindow* window, int width, int height);
void _window_close_callback();

#endif