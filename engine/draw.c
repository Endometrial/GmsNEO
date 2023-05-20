
#include <engine/draw.h>

Shader active_shader;

void draw_clear(float r, float g, float b, float a) {
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw_set_mode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void draw_indexed_mesh(Mesh mesh) {
	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.elements, GL_UNSIGNED_INT, 0);
}

void draw_mesh(Mesh mesh) {
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.elements);
}

void draw_set_texture(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void draw_set_shader(Shader shader) {
	active_shader = shader;
	glUseProgram(active_shader.program);
}

Shader draw_get_shader() {
	return active_shader;
}

void draw_sprite(Sprite sprite, float x, float y, float scale) {
	Shader shader;
	mat4 matrix;

	shader = draw_get_shader();
	glm_mat4_identity(matrix);
	glm_mat4_scale(matrix, scale);
	matrix[3][1] = x;
	matrix[3][0] = y;

	draw_set_texture(sprite.texture);
	shader_set_uniform_mat4(shader.program, "transform", matrix);
	draw_indexed_mesh(sprite.mesh);
}
