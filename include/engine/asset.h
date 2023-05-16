#ifndef ASSET_H
#define ASSET_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>
#include <engine/media.h>

typedef struct {
	Mesh mesh;
	unsigned int texture;
	Image image;
} Sprite;

Sprite asset_load_sprite(char* image_filepath, GLint texture_wrap, GLint texture_filter);
//Sound asset_load_sound();


#endif