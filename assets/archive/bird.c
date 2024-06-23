#include <stdio.h>
#include <baphomet/audio.h>
#include <baphomet/shader.h>
#include <baphomet/draw.h>
#include <baphomet/input.h>
#include <baphomet/camera.h>
#include <baphomet/room.h>

// Variables which are set at room load time
Object* id;
double x,y,z;

static char* texfp_bird = "assets/images/nature-images.png";
static char* sndfp_jump = "assets/audio/the-legendary-hero.ogg";

Texture tex_bird;
Mesh msh_bird;
Sound snd_jump;

static float floor_y = -18.5f;
static float ceiling_y = 30.0f;
static float jump_speed = 1.5f;
static float gravity = 0.08f;
static float terminal_v = 10.0f;
static float init_y = 0.0f;
static float init_x = -25.0f;

float vspeed;
int pressed;

void create() {
	//snd_jump = asset_load_sound(sndfp_jump);
	tex_bird = asset_load_texture(texfp_bird);
	msh_bird = mesh_generate_rect(5.0f, 5.0f);

	y = init_y;
	x = init_x;
	vspeed = 0;
}

float clamp(float val, float min, float max) {
	if (val > max)
		return max;
	if (val < min)
		return min;
	return val;
}

void step(float program_time, float delta_time) {
	vspeed -= gravity;
	if ((!pressed) && (key_press(VK_SPACE))) {
		pressed = 1;
		vspeed = jump_speed;
	}
	pressed = key_press(VK_SPACE);

	vspeed = clamp(vspeed, -terminal_v, terminal_v);

	y += vspeed;

	if (y>=ceiling_y) {
		y = ceiling_y;
		vspeed = 0.0f;
	}

	if (y<=floor_y) {
		y = floor_y;
		vspeed = 0.0f;
	}
}

void draw(float program_time, float delta_time) {
	draw_set_texture(tex_bird);
	draw_mesh_ext(msh_bird, x, y, 1.0f, 1.0f,1.0f,1.0f, 0.0f, 0.0f, y/1.5f);
}

void cleanup() {
	//asset_unload_sound(&snd_jump);
	asset_unload_texture(&tex_bird);
}

void destroy() {}
