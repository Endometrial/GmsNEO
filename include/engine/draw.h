#ifndef DRAW_H
#define DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>

void draw_clear(float r, float g, float b, float a);
void draw_set_mode(GLenum mode);
void draw_indexed_mesh(Mesh mesh);
void draw_mesh(Mesh mesh);

#endif