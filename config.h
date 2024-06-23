/*

  Baphomet Configuration

*/

/* General Program */
#include <X11/XF86keysym.h>

/* ///////////////////////////// PROJECT CONFIG ///////////////////////////// */



/* ////////////////////////////////// GLFW ////////////////////////////////// */

/* General */
#define GLFW_VERSION_MAJOR 3
#define GLFW_VERSION_MINOR 3
#define GLFW_PROFILE GLFW_OPENGL_CORE_PROFILE

/* Window */
static const uint window_width        = 640;
static const uint window_height	      = 480;
static const char window_name[]       = "Windowed";
static const uint default_sfact       = 302;
static const uint default_dfact       = 303;
static char default_fsh[]       = "assets/shaders/texture.fsh";
static char default_vsh[]       = "assets/shaders/transform.vsh";

/* ////////////////////////////// COMMAND LINE ////////////////////////////// */

const char* argp_program_bug_address             = "<autumn.hazel91@gmail.com>";
const char* argp_program_version                 = "baphomet v0.0.0a";
static char argp_program_desc[]                  = "a.out -- Test test";
static char argp_program_args_desc[]             = "[ARGS]";
static struct argp_option argp_program_options[] = {
  {"verbose",   'v',  0,  0,  "Produce debug related output"},
  {"debug",     'd',  0,  OPTION_ALIAS },
  {"quiet",     'q',  0,  0,  "Produce no output"},
  { 0 }};
