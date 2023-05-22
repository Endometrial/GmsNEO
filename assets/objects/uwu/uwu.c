#include <stdio.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <engine/draw.h>

Sprite pineapple;
Shader shader;
mat4 trans_matrix = GLM_MAT4_IDENTITY;
char* tex_filepath = "assets/images/nature-images.png";
char* vsh_filepath = "assets/shaders/engine/transform.vsh";
char* fsh_filepath = "assets/shaders/engine/texture.fsh";

float x, y;

void create() {
	pineapple = asset_load_sprite(tex_filepath, GL_REPEAT, GL_LINEAR);
	shader = shader_create(vsh_filepath, fsh_filepath);
}
void step(double program_time, double delta_time) {
	x = tan(program_time * 3.14f)/2;
	y = sin(program_time * 3.14f)/2;
}
void draw(double program_time, double delta_time) {
	//draw_set_shader(shader);
	draw_sprite(pineapple, x, y, 1.0f);
}
void cleanup() {
	printf("UwU cleanup\n");
}
void destroy() {
	printf("UwU destroy\n");
}