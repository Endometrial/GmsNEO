#include <stdio.h>
#include <baphomet/audio.h>
#include <baphomet/shader.h>
#include <baphomet/draw.h>
#include <baphomet/input.h>
#include <baphomet/camera.h>
#include <baphomet/room.h>
#include <decoder/file.h>

static int floor_height = 8.f;
static int floor_width = 80.f;

double x,y,z;

int indi_floor[6] = {3, 0, 1, 1, 2, 3};

static char* texfp_background = "assets/images/pineapple.png";
static char* texfp_floor = "assets/images/baphomet.png";
Mesh msh_background, msh_floor;
Texture tex_background, tex_floor;

static char* vshfp_loop = "assets/shaders/transform.vsh";
static char* fshfp_loop = "assets/shaders/loop.fsh";
Shader shd_loop, shd_default;

void create() {jnijjiji
	tex_background = asset_load_texture(texfp_background);
	tex_floor = asset_load_texture(texfp_floor);

	msh_background = mesh_generate_rect(80.0f, 60.0f);
	msh_floor = mesh_generate_rect(floor_width, floor_height);

	shd_default = draw_get_shader();
	shd_loop = shader_create(vshfp_loop, fshfp_loop);

	/*char** list = file_get_directory_files("assets");
	for (int i=0; (list[i]!=NULL); i++) {
		fprintf(stderr, "->%s\n", list[i]);
	}*/

}

void step(double program_time, double delta_time) {}

void draw(double program_time, double delta_time) {
	draw_set_tex_offset(program_time/80.0f, 0.0f);

	draw_set_texture(tex_background);
	draw_mesh_2d(msh_background, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	draw_set_tex_offset(program_time/10.0f, 0.0f);
	draw_set_tex_scale(10.0f, 1.0f);

	draw_set_texture(tex_floor);
	draw_mesh_2d(msh_floor, 0.0f, -25.0f, 1.0f, 0.0f, 0.0f);

	draw_set_tex_offset(0.0f, 0.0f);
	draw_set_tex_scale(1.0f, 1.0f);
}

void cleanup() {
	asset_unload_texture(&tex_background);
	asset_unload_texture(&tex_floor);
}

void destroy() {}
