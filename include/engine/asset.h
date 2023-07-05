#ifndef ASSET_H
#define ASSET_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>
#include <engine/media.h>
#include <engine/audio.h>
#include <engine/ogg.h>

static char* supported_image_filetypes[] = {"png", NULL};
static char* supported_audio_filetypes[] = {"ogg(vorbis)", NULL};

typedef struct {
	Mesh mesh;
	unsigned int texture;
	Image image;
} Sprite;

Sprite asset_load_sprite(char* filepath, GLint texture_wrap, GLint texture_filter);
Sound asset_load_sound(char* filepath);


#endif