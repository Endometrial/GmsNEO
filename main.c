#include "main.h"

char* snd_filepath = "/Users/user/Desktop/ogg/yume-nikki.ogg";

int main() {
	GLFWwindow* window;

	audio_initialize();
	window = window_initialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

	draw_set_shader(shader_create(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER));
	draw_set_blendmode(DEFAULT_SFACTOR_BLENDMODE, DEFAULT_DFACTOR_BLENDMODE);

	Room rm_default = room_load("./assets/rooms/default/default.xml");

	room_set(rm_default);
	room_execute_event(EVENT_CREATE);

	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		draw_clear(sin(program_time), sin(program_time+2.f), sin(program_time+4.f), 1.0f);

		room_execute_event(EVENT_STEP, program_time, delta_time);
		room_execute_event(EVENT_DRAW, program_time, delta_time);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	room_execute_event(EVENT_CLEANUP);

	window_terminate();
	audio_terminate();

	return 0;
}