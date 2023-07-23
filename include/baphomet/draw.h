#ifndef BAPHOMET_DRAW_H
#define BAPHOMET_DRAW_H

/*
	Draw.h
	Created: xxxx-xx-xx
	Description:
		Draw.h is a catchall for drawing
*/


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <baphomet/shader.h>
#include <baphomet/mesh.h>
#include <baphomet/texture.h>
#include <baphomet/camera.h>

#define GLFW_VERSION_MAJOR 3
#define GLFW_VERSION_MINOR 3

void draw_initialize();
void draw_terminate();
void draw_set_viewport(int width, int height);
void draw_clear(float r, float g, float b, float a);
void draw_set_mode(GLenum mode);
//void draw_indexed_mesh(Mesh mesh);
void draw_mesh_ext(Mesh mesh, float x, float y, float z, float x_scale, float y_scale, float z_scale, float x_rot, float y_rot, float z_rot);
void draw_mesh_2d(Mesh mesh, float x, float y, float scale, float rot, float depth);
void draw_set_texture(Texture texture);
void draw_set_texture_ext(Texture texture, GLint tex_wrap, GLint tex_filter);
void draw_set_tex_offset(float u, float v);
void draw_set_tex_scale(float u_scale, float v_scale);
void draw_set_shader(Shader shader);
void draw_set_blendmode(GLenum sfactor, GLenum dfactor);
Shader draw_get_shader();

//void draw_sprite(Sprite sprite, float x, float y, float scale);

#endif