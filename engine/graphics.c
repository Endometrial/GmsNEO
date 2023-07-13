#include <engine/graphics.h>

GLFWwindow* window;

GLFWwindow* window_initialize(int width, int height, const char* title) {
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
	glfwSetFramebufferSizeCallback(window, window_framebuffer_size_callback);

	// TODO: what in the goddamn fuck is this notation
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad :(");
	}


	glViewport(0,0,width,height);

	return window;
}

void window_terminate() {
	glfwTerminate();
}

GLFWwindow* window_get_active_pointer() {
	if (!window) {
		printf("No active window found?");
		exit(-1);
	}
	return window;
}

void _framebuffer_callback_direct_scale(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}