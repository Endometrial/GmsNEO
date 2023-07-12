#ifndef BAPHOMET_ASSET_H
#define BAPHOMET_ASSET_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/mesh.h>
#include <engine/audio.h>
#include <engine/png.h>
#include <engine/texture.h>
#include <engine/ogg.h>
#include <png.h>

static char* supported_image_filetypes[] = {"png\0", NULL};
static char* supported_audio_filetypes[] = {"ogg(vorbis)\0", NULL};

Texture asset_load_texture(char* filepath, GLint texture_wrap, GLint texture_filter);
void asset_unload_texture(Texture* texture);
Sound asset_load_sound(char* filepath);
void asset_unload_sound(Sound* sound);

#endif