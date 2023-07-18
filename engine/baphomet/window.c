#include <baphomet/window.h>

Window* window;

Window* window_initialize(int width, int height, const char* title) {
	if (!glfwInit()) {
		printf("Failed to initialize glfw :(");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(width, height, title, NULL, NULL);
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

	glViewport(0,0,width,height);

	return window;
}

void window_close_active() {
	window_close(window_get_active());
}

void window_close(Window* window) {
	glfwSetWindowShouldClose(window, 1);
}

void window_terminate() {
	glfwTerminate();
}

Window* window_get_active() {
	if (!window) {
		printf("No active window found?");
		exit(-1);
	}
	return window;
}

void _window_close_callback(GLFWwindow* window) {
	glfwSetWindowShouldClose(window, 1);
}

void _framebuffer_callback_direct_scale(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}