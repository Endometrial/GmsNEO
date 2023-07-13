#ifndef BAPHOMET_DRAW_H
#define BAPHOMET_DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>

#include <baphomet/mesh.h>
#include <baphomet/asset.h>
#include <baphomet/shader.h>
#include <baphomet/camera.h>


void draw_clear(float r, float g, float b, float a);
void draw_set_mode(GLenum mode);
//void draw_indexed_mesh(Mesh mesh);
void draw_mesh(Mesh mesh, float x, float y, float scale);
void draw_set_texture(Texture texture);
void draw_set_shader(Shader shader);
void draw_set_blendmode(GLenum sfactor, GLenum dfactor);
Shader draw_get_shader();

//void draw_sprite(Sprite sprite, float x, float y, float scale);

#endif