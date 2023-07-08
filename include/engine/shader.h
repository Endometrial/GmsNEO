#ifndef BAPHOMET_SHADER_H
#define BAPHOMET_SHADER_H

#include <stdarg.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/mat4.h>
#include <engine/file.h>

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1
#define SHADER_NUM 2

typedef struct {
	unsigned int* shader;
	unsigned int program;
} Shader;

Shader shader_create(char* vsh_filepath, char* fsh_filepath);
unsigned int shader_build_type(char* filepath, int type);
void shader_set_uniform_vec4(unsigned int program, char* name, float x, float y, float z, float w);
void shader_set_uniform_float(unsigned int program, char* name, float val);
void shader_set_uniform_int(unsigned int program, char* name, int val);
void shader_set_uniform_mat4(unsigned int program, char* name, mat4 matrix);

#endif
