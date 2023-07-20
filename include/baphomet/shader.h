#ifndef BAPHOMET_SHADER_H
#define BAPHOMET_SHADER_H

/*
	Shader.h
	Created: xxxx-xx-xx
	Description:
		Shader.h is a poorly coded set of scripts for
		shader creation and manipulation (but not
		application??... thanks draw.h)
*/

#include <stdarg.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/mat4.h>

#include <decoder/file.h>

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1
#define SHADER_NUM 2

typedef struct {
	unsigned int* shader;
	unsigned int program;
} Shader;

Shader shader_create(char* vsh_filepath, char* fsh_filepath);
unsigned int shader_build_type(char* filepath, int type);
void shader_set_uniform_vec4(Shader shader, char* name, float x, float y, float z, float w);
void shader_set_uniform_float(Shader shader, char* name, float val);
void shader_set_uniform_int(Shader shader, char* name, int val);
void shader_set_uniform_mat4(Shader shader, char* name, mat4 matrix);

#endif
