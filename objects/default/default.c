#include <stdio.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <engine/draw.h>
#include <engine/input.h>

Sprite pineapple;
char* tex_filepath = "assets/images/pineapple.png";
float x, y = 0.0f;
float run_spd = 0.01f;
int hspeed, vspeed;

void create() {
	pineapple = asset_load_sprite(tex_filepath, GL_REPEAT, GL_LINEAR);
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