#include "main.h"

int main() {
	GLFWwindow* window;


	audio_initialize();
	window = window_initialize(800,600,"Tile");
	//shader = shader_create(vsh_filepath, fsh_filepath);

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
	audio_terminate();

	return 0;
}
