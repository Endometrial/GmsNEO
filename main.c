#include "main.h"

int main() {
	GLFWwindow* window;

	window = window_initialize(800,600,"Tile");

	default_create();

	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		default_step(delta_time,program_time);

		default_draw(delta_time,program_time);
	
		default_clean();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
