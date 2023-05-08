#ifndef SHADER_H
#define SHADER_H

#include <engine/media.h>
#include <stdarg.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int shader_build(char* filepath, int type);
unsigned int shader_program_create(unsigned int shader, ...);
void shader_program_apply(unsigned int program);
void shader_set_uniform_vec4(unsigned int program, char* name, float x, float y, float z, float w);
void shader_set_uniform_float(unsigned int program, char* name, float val);
void shader_set_uniform_int(unsigned int program, char* name, int val);

#endif
