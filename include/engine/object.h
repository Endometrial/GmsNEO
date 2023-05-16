#include <engine/draw.h>
#include <engine/input.h>
#include <engine/media.h>
#include <engine/mesh.h>
#include <engine/shader.h>
#include <engine/audio.h>
#include <cglm/call.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>

void default_create();
void default_step(double delta_time, double program_time);
void default_draw(double delta_time, double program_time);
void default_clean();
void default_destroy();