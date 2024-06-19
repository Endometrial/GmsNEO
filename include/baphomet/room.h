#ifndef BAPHOMET_ROOM_H
#define BAPHOMET_ROOM_H

/*
	Room.h
	Created: xxxx-xx-xx
	Description:
		Room.h is a catchall for room manipulation
		with the exception of room loading
*/

#include <decoder/xml.h>
#include <baphomet/object.h>
#include <baphomet/tools.h>

static char* hexedecimal_pointer_textformat_regex	= "(?<=^0p)[0-9a-fA-F]+$";
static char* hexedecimal_int_textformat_regex		= "(?<=^0x)[0-9a-fA-F]+$";
static char* binary_int_textformat_regex			= "(?<=^0b)[0-1]+$";
static char* double_float_textformat_regex			= "^-?(([0-9])+\\.([0-9]?)+)|(([0-9]?)+\\.([0-9])+)((?=f$)|$)";
static char* long_int_textformat_regex				= "^-?[0-9]+((?=i|d|u)|$)";

typedef struct {
	Object* instance_list;
	int num_instances;
} Room;

Room asset_load_room(char* filepath);
void asset_unload_room(Room* room);

Room* room_get();
void room_set();
void room_execute_event(int event, ...);

#endif
