#include "main.h"

int main() {
	GLFWwindow* window;

	audio_initialize();
	window = window_initialize(800,600,"Tile");

	draw_set_shader(shader_create(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER));

	Object nya, uwu;
	nya = object_load("./assets/objects/default/default.c.so");
	uwu = object_load("./assets/objects/uwu/uwu.c.so");

	//default_create();
	nya.create();
	uwu.create();


	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		draw_clear(0.0f, 0.0f, 0.0f, 1.0f);

		nya.step(program_time, delta_time);
		uwu.step(program_time, delta_time);
		nya.draw(program_time, delta_time);
		uwu.draw(program_time, delta_time);
		//default_step(delta_time,program_time);

		//default_draw(delta_time,program_time);
	
		//default_clean();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	nya.destroy();
	uwu.destroy();
	nya.cleanup();
	uwu.cleanup();

	glfwTerminate();
	audio_terminate();

	return 0;
}