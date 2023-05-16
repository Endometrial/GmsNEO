#include <engine/object.h>

//
// Default Object
//

static float verticies[] = {
	-.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -.5f, 0.0f, 1.0f, 0.0f,
	-.5f, -.5f, 0.0f, 0.0f, 0.0f,
};
static int indicies[] = {
	3, 0, 1,
	1, 2, 3
};
mat4 matrix = GLM_MAT4_IDENTITY;
static char* vsh_filepath = "shaders/engine/transform.vsh";
static char* fsh_filepath = "shaders/engine/texture.fsh";
static char* tex_filepath = "assets/images/nature-images.png";


Mesh mesh;
unsigned int texture, vsh, fsh, shader_program;
PaStream* stream;
//float* transformation_matrix;

// Create event for the initialization phaze
void default_create() {
	texture = image_load_texture(tex_filepath, GL_REPEAT, GL_NEAREST);

	mesh = mesh_initialize();
	mesh = mesh_add_indexed_vertices(mesh, GL_STATIC_DRAW, verticies, sizeof(verticies), indicies, sizeof(indicies));
	mesh_build();
	vsh = shader_build(vsh_filepath, GL_VERTEX_SHADER);
	fsh = shader_build(fsh_filepath, GL_FRAGMENT_SHADER);
	shader_program = shader_program_create(vsh, fsh);

	audio_initialize();
	//stream = audio_open_stream(0,2,44100,&audio_callback);
	/*transformation_matrix = math_fmatrix_create(4,4,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);*/
	Sound audio = audio_play_callback_async(1l);
}

// Step event for actions every frame
void default_step(double delta_time, double program_time) {
	//audio_play_stream(stream);
	//Pa_Sleep(1000*1);
	//audio_stop_stream(stream);
	//audio_play_callback_async(2);
	double x = cos(program_time*3.14) * 0.5;
	double y = sin(program_time*3.14) * 0.5;
	matrix[3][1] = x;
	matrix[3][0] = y;
}

// Draw event for drawing stuff :3
void default_draw(double delta_time, double program_time) {

	draw_set_mode(GL_TRIANGLES);
	draw_clear(0.5f, 0.5f, 0.5f, 1.0f);

	shader_program_apply(shader_program);
	shader_set_uniform_mat4(shader_program, "transform", matrix);
	draw_set_texture(texture);
	draw_indexed_mesh(mesh);
}

// Clean event for room changes or game endings
void default_clean() {

}

// Destroy event in the case the object gets deleted
void default_destroy() {

}
