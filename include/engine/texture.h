#ifndef BAPHOMET_TEXTURE_H
#define BAPHOMET_TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>
#include <engine/png.h>

#define DEFAULT_TEXTURE_WRAP 0x0
#define DEFAULT_TEXTURE_FILTER 0x0

#define IMG_TYPE_UNKNOWN 0x0
#define IMG_TYPE_PNG	 0x1

typedef struct {
	unsigned int texture;
	void*		user_data;
	int			type;
} Texture;

//int texture_get_bit_depth(Texture* texture);
//int texture_get_color_type(Texture texture);
//unsigned int texture_get_width(Texture texture);
unsigned int texture_get_height(Texture texture);

#endif