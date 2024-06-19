#include <baphomet/window.h>

Window* active_window;

Window* window_create(int width, int height, const char* title) {
	Window* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		printf("Failed to create window :(");
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, DEFAULT_FBUF_CALLBACK);
	glfwSetWindowCloseCallback(window, DEFAULT_CLOSE_CALLBACK);

	// TODO: what in the goddamn fuck is this notation
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad :(");
	}

	active_window = window;
	return active_window;
}

void window_destroy(Window* window) {
	glfwSetWindowShouldClose(window, 1);
}

Window* window_get_active() {
	return active_window;
}

void window_set_active(Window* window) {
	glfwMakeContextCurrent(window);
	active_window = window;
}

void _window_close_callback(GLFWwindow* window) {
	glfwSetWindowShouldClose(window, 1);
}

void _framebuffer_callback_direct_scale(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
