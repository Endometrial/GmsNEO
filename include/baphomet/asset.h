#ifndef BAPHOMET_ASSET_H
#define BAPHOMET_ASSET_H

#include <baphomet/audio.h>
#include <baphomet/texture.h>
#include <baphomet/room.h>
#include <baphomet/object.h>

static char* supported_image_filetypes[] = {"png\0", NULL};
static char* supported_audio_filetypes[] = {"ogg(vorbis)\0", NULL};

Texture asset_load_texture(char* filepath, GLint texture_wrap, GLint texture_filter);
void asset_unload_texture(Texture* texture);
Sound asset_load_sound(char* filepath);
void asset_unload_sound(Sound* sound);
Room asset_load_room(char* filepath);
void asset_unload_room(Room* room);
Object asset_load_object(char* filepath);
void asset_unload_object(Object* object);

#endif