#include "main.h"

char* snd_filepath = "/Users/user/Desktop/ogg/yume-nikki.ogg";

int main() {
	GLFWwindow* window;
	OggDecoder* decoder;
	Samplei16 sample;
	int eos = 0;

	decoder = ogg_decoder_open(snd_filepath);

	ogg_sample_initialize_i16(&sample);
	while((ogg_decoder_get_pcm_i16(decoder, &sample)) != 1) {}

	ogg_decoder_close(decoder);

	audio_initialize();
	window = window_initialize(800,600,"Tile");

	draw_set_shader(shader_create(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER));

	Room rm_default = room_load("./assets/rooms/default/default.xml");

	room_set(rm_default);
	room_execute_event(EVENT_CREATE);

	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		draw_clear(0.0f, 0.0f, 0.0f, 1.0f);

		room_execute_event(EVENT_STEP, program_time, delta_time);
		room_execute_event(EVENT_DRAW, program_time, delta_time);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	room_execute_event(EVENT_CLEANUP);

	glfwTerminate();
	audio_terminate();

	return 0;
}