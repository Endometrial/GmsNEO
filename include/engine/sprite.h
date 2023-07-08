#ifndef BAPHOMET_SPRITE_H
#define BAPHOMET_SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>

#define DEFAULT_TEXTURE_WRAP 0x0
#define DEFAULT_TEXTURE_FILTER 0x0

#define IMG_TYPE_UNKNOWN 0x0
#define IMG_TYPE_PNG	 0x1

typedef struct {
	Mesh 		mesh;
	unsigned int texture;
	void*		user_data;
	int			type;
} Sprite;

// Do stuff here

#endif