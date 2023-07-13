#include <stdio.h>
#include <baphomet/asset.h>
#include <baphomet/shader.h>
#include <baphomet/draw.h>
#include <baphomet/input.h>
#include <baphomet/camera.h>
#include <baphomet/room.h>

static char* sndfp_background = "assets/audio/the-legendary-hero.ogg";
Sound snd_background;

void create() {
	audio_set_input_device(0); // Built-in Microphone
	audio_set_output_device(1); // JBL TUNE750BTNC

	camera_set_projection_ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.001f, 10000.0f);
	camera_set_view_lookat(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);

	snd_background = asset_load_sound(sndfp_background);
	//audio_sound_play(snd_background);
}

void step(double program_time, double delta_time) {
	if (key_press(VK_ESCAPE)) {
		exit(-1);
	}
}

void draw(double program_time, double delta_time) {}

void cleanup() {
	asset_unload_sound(&snd_background);
}

void destroy() {
	fprintf(stderr, "Game object destroyed!");
}
