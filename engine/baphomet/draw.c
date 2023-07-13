#include <baphomet/draw.h>

Shader active_shader;

void draw_clear(float r, float g, float b, float a) {
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw_set_mode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void draw_mesh(Mesh mesh, float x, float y, float scale) {
	mat4 local_matrix;
	Shader shader;
	shader = draw_get_shader();
	glm_mat4_identity(local_matrix);
	glm_mat4_scale(local_matrix, scale);
	local_matrix[3][1] = y;
	local_matrix[3][0] = x;

	shader_set_uniform_mat4(shader, "local_matrix", local_matrix);
	shader_set_uniform_mat4(shader, "projection_matrix", *camera_get_projection_matrix());
	shader_set_uniform_mat4(shader, "view_matrix", *camera_get_view_matrix());

	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.elements, GL_UNSIGNED_INT, 0);
}

//void draw_mesh(Mesh mesh) { // All meshes are now indexed meshes
//	glBindVertexArray(mesh.vao);
//	glDrawArrays(GL_TRIANGLES, 0, mesh.elements);
//}

void draw_set_texture(Texture texture) {
	glBindTexture(GL_TEXTURE_2D, texture.texture);
}

void draw_set_shader(Shader shader) {
	active_shader = shader;
	glUseProgram(active_shader.program);
}

Shader draw_get_shader() {
	return active_shader;
}

void draw_set_blendmode(GLenum sfactor, GLenum dfactor) {
	glBlendFunc(sfactor, dfactor);
	glEnable(GL_BLEND);
}

/*
void draw_sprite(Sprite sprite, float x, float y, float scale) {
	mat4 local_matrix;
	Shader shader;
	shader = draw_get_shader();
	glm_mat4_identity(local_matrix);
	glm_mat4_scale(local_matrix, scale);
	local_matrix[3][1] = x;
	local_matrix[3][0] = y;

	shader_set_uniform_mat4(shader.program, "local_matrix", local_matrix);
	shader_set_uniform_mat4(shader.program, "projection_matrix", *camera_get_projection_matrix());
	shader_set_uniform_mat4(shader.program, "view_matrix", *camera_get_view_matrix());
	draw_set_texture(sprite.texture);
	draw_indexed_mesh(sprite.mesh);
}*/
