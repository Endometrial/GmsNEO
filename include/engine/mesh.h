#ifndef BAPHOMET_MESH_H
#define BAPHOMET_MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define VERTEX_ATTRUBUTES 5;

typedef struct Mesh {
	unsigned int vao;
	unsigned int elements;
} Mesh;

Mesh mesh_initialize();
Mesh mesh_add_vertices(Mesh mesh, GLenum mode, float* vertices, size_t size);
Mesh mesh_add_indexed_vertices(Mesh mesh, GLenum mode, float* vertices, size_t sizev, unsigned int* indices, size_t sizei);
void mesh_build();

Mesh mesh_generate_rect(float width, float height);
//Mesh mesh_generate_circle(float radius, float height);

#endif