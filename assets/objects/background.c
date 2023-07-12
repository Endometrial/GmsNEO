#include <stdio.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <engine/draw.h>
#include <engine/input.h>
#include <engine/camera.h>
#include <engine/room.h>
#include <engine/ogg.h>
#include <engine/ogg.h>

static int floor_height = 8.f;
static int floor_width = 80.f;

int indi_floor[6] = {3, 0, 1, 1, 2, 3};

static char* texfp_background = "assets/images/baphomet.png";
static char* texfp_floor = "assets/images/baphomet.png";
Mesh msh_background, msh_floor;
Texture tex_background, tex_floor;

static char* vshfp_loop = "assets/shaders/transform.vsh";
static char* fshfp_loop = "assets/shaders/loop.fsh";
Shader shd_loop, shd_default;

void create() {
	float vert_floor[20] = {
		-floor_width/2,  floor_height/2, 0.0f, 0.0f,                     1.0f,
		 floor_width/2,  floor_height/2, 0.0f, floor_width/floor_height, 1.0f,
		 floor_width/2, -floor_height/2, 0.0f, floor_width/floor_height, 0.0f,
		-floor_width/2, -floor_height/2, 0.0f, 0.0f,                     0.0f };

	tex_background = asset_load_texture(texfp_background, GL_REPEAT, GL_LINEAR);
	tex_floor = asset_load_texture(texfp_floor, GL_REPEAT, GL_LINEAR);

	msh_background = mesh_generate_rect(80.0f, 60.0f);
	msh_floor = mesh_generate_vertices(GL_STATIC_DRAW, DEFAULT_VERTEX_FORMAT, vert_floor, 20, indi_floor, 6);

	shd_default = draw_get_shader();
	shd_loop = shader_create(vshfp_loop, fshfp_loop);
}

void step(double program_time, double delta_time) {}

void draw(double program_time, double delta_time) {
	draw_set_shader(shd_loop);
	shader_set_uniform_float(shd_loop, "loop_offset", program_time/40.0f);
	draw_set_texture(tex_background);
	draw_mesh(msh_background, 0.0f, 0.0f, 1.0f);

	shader_set_uniform_float(shd_loop, "loop_offset", program_time);
	draw_set_texture(tex_floor);
	draw_mesh(msh_floor, 0.0f, -25.0f, 1.0f);
	draw_set_shader(shd_default);
}

void cleanup() {
	asset_unload_texture(&tex_background);
	asset_unload_texture(&tex_floor);
}

void destroy() {}
