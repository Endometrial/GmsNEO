
#include <engine/draw.h>

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
