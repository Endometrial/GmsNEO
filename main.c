#include "main.h"

int main() {
	GLFWwindow* window;


	audio_initialize();
	window = window_initialize(800,600,"Tile");
	//shader = shader_create(vsh_filepath, fsh_filepath);
	Object nya, uwu;
	nya = object_load("./objects/default/default.c.so");
	uwu = object_load("./objects/uwu/uwu.c.so");

	//default_create();
	nya.create();
	uwu.create();


	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		nya.step();
		uwu.step();
		nya.draw();
		uwu.draw();
		nya.cleanup();
		uwu.cleanup();
		//default_step(delta_time,program_time);

		//default_draw(delta_time,program_time);
	
		//default_clean();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	nya.destroy();
	uwu.destroy();

	glfwTerminate();
	audio_terminate();

	return 0;
}
