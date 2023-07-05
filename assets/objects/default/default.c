#include <stdio.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <engine/draw.h>
#include <engine/input.h>
#include <engine/camera.h>
#include <engine/room.h>
#include <engine/ogg.h>

Sprite pineapple;
Sound sound;
char* tex_filepath = "assets/images/pineapple.png";
char* snd_filepath = "/Users/user/Desktop/ogg/yume-nikki.ogg";
float x, y = 0.0f;
float run_spd = 0.02f;
int hspeed, vspeed;

void create() {
	audio_set_input_device(2); // Built-in Microphone
	audio_set_output_device(1); // JBL TUNE750BTNC

	camera_set_projection_perspective(3.141f/4.0f, 800.0f/600.0f, 0.1f, 100.0f);
	//camera_set_projection_ortho(-40.0f, 40.0f, -30.0f, 30.0f, 0.001f, 10000.0f);
	camera_set_view_lookat(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);
	pineapple = asset_load_sprite(tex_filepath, GL_REPEAT, GL_LINEAR);

	sound = asset_load_sound(snd_filepath);
	audio_sound_play(sound);
	//fprintf(stderr,"Error?\n");exit(-1);
}
void step(double program_time, double delta_time) {
	hspeed = key_press(VK_UP) - key_press(VK_DOWN);
	vspeed = key_press(VK_RIGHT) - key_press(VK_LEFT);

	x += run_spd * (float)hspeed;
	y += run_spd * (float)vspeed;
}
void draw(double program_time, double delta_time) {
	draw_sprite(pineapple, x, y, 1.0f);
}
void cleanup() {
	printf("Nya cleanup\n");
}
void destroy() {
	printf("Nya destroy\n");
}