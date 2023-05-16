#ifndef DRAW_H
#define DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>
#include <engine/asset.h>
#include <engine/shader.h>
#include <cglm/cglm.h>
#include <cglm/mat4.h>

void draw_clear(float r, float g, float b, float a);
void draw_set_mode(GLenum mode);
void draw_indexed_mesh(Mesh mesh);
void draw_mesh(Mesh mesh);
void draw_set_texture(GLuint texture);
void draw_set_shader(Shader shader);

void draw_sprite(Sprite sprite, float x, float y, float scale);

#endif