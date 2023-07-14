#ifndef BAPHOMET_MESH_H
#define BAPHOMET_MESH_H

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 								  		xyzuvrgba
#define VERTEX_FORMAT_UV 	0x3 << 4 // 000110000
#define VERTEX_FORMAT_XY 	0x3 << 7 // 110000000
#define VERTEX_FORMAT_XYZ 	0x7 << 6 // 111000000
#define VERTEX_FORMAT_RGB   0x7 << 1 // 000001110
#define VERTEX_FORMAT_RGBA  0xF << 0 // 000001111
#define DEFAULT_VERTEX_FORMAT (VERTEX_FORMAT_XYZ | VERTEX_FORMAT_UV) // Nobody uses rgba

typedef struct Mesh {
	unsigned int vao;
	unsigned int elements;
	int 		 format;
} Mesh;

Mesh mesh_generate_rect(float width, float height);
//Mesh mesh_generate_circle(float radius, float subdivisions;
//Mesh mesh_generate_tri(float x1, float y1, float x2, float y2, float x3, float y3);
Mesh mesh_generate_vertices(GLenum mode, int format, float* vertices, int vnum, int* indices, int inum);

int mesh_format_elements(int format);
void mesh_format_enable(int format);

Mesh mesh_start(int format);
Mesh mesh_add_vertices(Mesh mesh, GLenum mode, float* vertices, size_t velements, int* indices, size_t ielements);
void mesh_finish(Mesh mesh);

#endif