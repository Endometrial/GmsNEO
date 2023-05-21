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

void create() {
	pineapple = asset_load_sprite(tex_filepath, GL_REPEAT, GL_LINEAR);
	shader = shader_create(vsh_filepath, fsh_filepath);
}
void step(double program_time, double delta_time) {
	trans_matrix[3][1] = tan(program_time * 3.14f)/2;
	trans_matrix[3][0] = sin(program_time * 3.14f)/2;
}
void draw(double program_time, double delta_time) {
	draw_set_shader(shader);
	shader_set_uniform_mat4(shader.program, "transform", trans_matrix);
	draw_sprite(pineapple, sin(program_time * 3.14f)/2, tan(program_time * 3.14f)/2, 1.0f);
}
void cleanup() {
	printf("UwU cleanup\n");
}
void destroy() {
	printf("UwU destroy\n");
}