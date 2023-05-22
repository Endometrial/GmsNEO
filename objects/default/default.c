#include <stdio.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <engine/draw.h>
#include <engine/input.h>
#include <engine/camera.h>

Sprite pineapple;
char* tex_filepath = "assets/images/pineapple.png";
float x, y = 0.0f;
float run_spd = 0.02f;
int hspeed, vspeed;

void create() {
	camera_set_projection_perspective(3.141f/4.0f, 800.0f/600.0f, 0.1f, 100.0f);
	//camera_set_projection_ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.001f, 10000.0f);
	camera_set_view_lookat(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f);
	pineapple = asset_load_sprite(tex_filepath, GL_REPEAT, GL_LINEAR);
}
void step(double program_time, double delta_time) {
	hspeed = key_press(VK_UP) - key_press(VK_DOWN);
	vspeed = key_press(VK_RIGHT) - key_press(VK_LEFT);

	camera_set_view_lookat(cos(x)+cos(y), cos(x)+sin(y), sin(x)+sin(y)+1.0, 0.0f, 0.0f, 0.0f);
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