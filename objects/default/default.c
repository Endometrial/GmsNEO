#include <engine/object.h>

mat4 matrix = GLM_MAT4_IDENTITY;
static char* vsh_filepath = "shaders/engine/transform.vsh";
static char* fsh_filepath = "shaders/engine/texture.fsh";
static char* tex_filepath = "assets/images/pineapple.png";

Mesh mesh;
Sprite sprite;
Shader shader;

void default_create() {
	sprite = asset_load_sprite(tex_filepath, GL_REPEAT, GL_NEAREST);
	mesh = mesh_generate_rect(1.0f, 1.0f);
	shader = shader_create(vsh_filepath, fsh_filepath);

}

void default_step(double delta_time, double program_time) {

	double x = tan(program_time*3.14) * 0.5;
	double y = sin(program_time*3.14) * 0.5;
	matrix[3][1] = x;
	matrix[3][0] = y;
}

void default_draw(double delta_time, double program_time) {

	draw_set_mode(GL_TRIANGLES);
	//draw_clear(0.5f, 0.5f, 0.5f, 1.0f);

	draw_set_shader(shader);
	shader_set_uniform_mat4(shader.program, "transform", matrix);
	draw_sprite(sprite, 0, 0, 1);
}

void default_clean() {

}
