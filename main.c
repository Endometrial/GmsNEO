#include "main.h"

int main() {
	GLFWwindow* window;

	window = window_initialize(800,600,"Tile");

	while (!glfwWindowShouldClose(window)) {

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
