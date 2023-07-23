#ifndef BAPHOMET_TEXTURE_H
#define BAPHOMET_TEXTURE_H

/*
	Texture.h
	Created: xxxx-xx-xx
	Description:
		Texture.h is a severly neglected (for now)
		set of scripts for texture manipulation
		will come to include sampling and other
		nice things
*/

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <decoder/png.h>

#define DEFAULT_TEXTURE_WRAP	GL_REPEAT
#define DEFAULT_TEXTURE_FILTER  GL_LINEAR

#define IMG_TYPE_UNKNOWN 0x0
#define IMG_TYPE_PNG	 0x1

static char* supported_image_filetypes[] = {"png\0", NULL};

typedef struct {
	unsigned int texture;
	void*		user_data;
	int			type;
} Texture;

Texture asset_load_texture(char* filepath);
void asset_unload_texture(Texture* texture);

int texture_get_bit_depth(Texture* texture);
int texture_get_color_type(Texture texture);
unsigned int texture_get_width(Texture texture);
unsigned int texture_get_height(Texture texture);

#endif