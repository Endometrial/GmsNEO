#include "main.h"

int main() {
	GLFWwindow* window;

	window = window_initialize(800,600,"Tile");

	default_create();

	double programtime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double deltatime = programtime - glfwGetTime();
		programtime = glfwGetTime();

		default_step(deltatime);

		default_draw(deltatime);
	
		default_clean();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
