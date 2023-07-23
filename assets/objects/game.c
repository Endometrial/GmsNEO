#include <stdio.h>
#include <baphomet/audio.h>
#include <baphomet/shader.h>
#include <baphomet/draw.h>
#include <baphomet/input.h>
#include <baphomet/camera.h>
#include <baphomet/room.h>

static char* sndfp_background = "assets/audio/the-legendary-hero.ogg";
Sound snd_background;

Object* id;
double x,y,z;

void create() {
	audio_set_input_device(audio_get_default_input_device());
	audio_set_output_device(audio_get_default_output_device());

	camera_set_projection_ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.001f, 10000.0f);
	camera_set_view_lookat(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);

	snd_background = asset_load_sound(sndfp_background);
	audio_sound_play(snd_background, 1);
}

void step(double program_time, double delta_time) {
	if (key_press(VK_ESCAPE)) {
		window_destroy(window_get_active());
	}
}

void draw(double program_time, double delta_time) {}

void cleanup() {
	asset_unload_sound(&snd_background);
}

void destroy() {
	fprintf(stderr, "Game object destroyed!\n");
}
