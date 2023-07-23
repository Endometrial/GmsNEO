#include "main.h"

char* project_filepath = "assets/project.xml";

int main() {
	Room rm_default;
	Window* window;

	// Initialize systems
	draw_initialize();
	audio_initialize();

	// Parse project xml
	project_open_xml(project_filepath);

	// Get project data NOTE: If defined as char* win_name, room_fp etc.. not enough data is statically allocated
	char* win_name = project_get_default_window_name();
	char* room_fp = project_get_default_room_filepath();
	char* vsh_fp = project_get_default_vertex_shader_filepath();
	char* fsh_fp = project_get_default_fragment_shader_filepath();
	char* obj_dir = project_get_default_object_directory();
	char* rm_dir = project_get_default_room_directory();
	int width = project_get_default_window_width();
	int height = project_get_default_window_height();
	int fbuf = project_get_default_framebuffer_callback();
	int dfac = project_get_default_dfactor_blendmode();
	int sfac = project_get_default_sfactor_blendmode();

	// Create window
	window = window_create(width, height, win_name);
	draw_set_viewport(width, height);

	// Set defaults
	draw_set_shader(shader_create(vsh_fp, fsh_fp));
	draw_set_blendmode(sfac, dfac);
	rm_default = asset_load_room(room_fp);
	room_set(rm_default);

	// Begin game loop & execute events
	room_execute_event(EVENT_CREATE);
	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window_get_active())) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();

		room_execute_event(EVENT_STEP, program_time, delta_time);
		room_execute_event(EVENT_DRAW, program_time, delta_time);
		
		glfwSwapBuffers(window_get_active());
		glfwPollEvents();
	}
	room_execute_event(EVENT_CLEANUP);
	room_execute_event(EVENT_DESTROY);

	// Unload current room
	asset_unload_room(room_get());

	// Terminate systems
	draw_terminate();
	audio_terminate();

	// Free unneeded project data
	project_close();

	return 0;
}