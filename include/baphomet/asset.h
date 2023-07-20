#ifndef BAPHOMET_ASSET_H
#define BAPHOMET_ASSET_H

/*
	Asset.h
	Created: xxxx-xx-xx
	Description:
		Asset.h is intened to house scripts which 
		load/unload various assets into memory.
		This list currently includes:
			* Textures
			* Sounds
			* Rooms
			* Objects
*/

#include <baphomet/audio.h>
#include <baphomet/texture.h>
#include <baphomet/room.h>
#include <baphomet/object.h>

static char* supported_image_filetypes[] = {"png\0", NULL};
static char* supported_audio_filetypes[] = {"ogg(vorbis)\0", NULL};

// To be migrated into room.h
// Find way to make more satisfying
static char* hexedecimal_pointer_textformat_regex	= "(?<=^0p)[0-9a-fA-F]+$";
static char* hexedecimal_int_textformat_regex		= "(?<=^0x)[0-9a-fA-F]+$";
static char* binary_int_textformat_regex			= "(?<=^0b)[0-1]+$";
static char* double_float_textformat_regex			= "^-?(([0-9])+\\.([0-9]?)+)|(([0-9]?)+\\.([0-9])+)((?=f$)|$)";
static char* long_int_textformat_regex				= "^-?[0-9]+";

Texture asset_load_texture(char* filepath, GLint texture_wrap, GLint texture_filter);
void asset_unload_texture(Texture* texture);
Sound asset_load_sound(char* filepath);
void asset_unload_sound(Sound* sound);
Room asset_load_room(char* filepath);
void asset_unload_room(Room* room);
Object asset_load_object(char* filepath);
void asset_unload_object(Object* object);

#endif