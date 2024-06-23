#include "main.h"

struct arguments { int debug, quiet; };
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;
  switch(key) {
    case 'v': case 'd':
      arguments->debug = 1;
      break;
    case 'q':
      arguments->quiet = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
        argp_usage(state);
    case ARGP_KEY_END:
      if (state->arg_num >= 2)
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

struct argp argp = { argp_program_options, parse_opt, argp_program_args_desc, argp_program_desc };
int main(int argc, char* argv[]) {
	struct arguments cmd_args = {.debug = 0, .quiet = 0};
	Window* window;

	// Parse ARGS
	argp_parse(&argp, argc, argv, 0, 0, &cmd_args);
	(cmd_args.debug) ? fprintf(stderr,"\tDEBUG ENABLED:\n"):0;

	// Initialize systems (REPLACE MOST OF THE FOLLOWING WITH SYSINIT(flags, etc...))
	draw_initialize();
	audio_initialize();

	// Create window
	window = window_create(window_width, window_height, window_name);
	draw_set_viewport(window_width, window_height);

	// Set defaults
	draw_set_shader(shader_create(default_vsh, default_fsh));
	draw_set_blendmode(default_sfact, default_dfact);


  queue_add_objects(cats, 2);
  queue_add_objects(cake, 1);
  queue_execute_event(EVENT_CREATE, -1);


	double program_time = glfwGetTime();
	while (!glfwWindowShouldClose(window_get_active())) {
		double delta_time = program_time - glfwGetTime();
		program_time = glfwGetTime();
		draw_clear(0.5f, 0.5f, 0.5f, 1.0f);

    queue_execute_event(EVENT_STEP, delta_time);

		glfwSwapBuffers(window_get_active());
		glfwPollEvents();

    if (key_press(VK_ESCAPE)) {
      glfwSetWindowShouldClose(window_get_active(), GL_TRUE);
    }
	}

  // Remove objects
  //queue_remove_object(0);
  //queue_remove_object(1);
  queue_cleanup();

	// Terminate systems
	draw_terminate();
	audio_terminate();

	return 0;
}
