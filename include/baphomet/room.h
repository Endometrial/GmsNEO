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

typedef struct {
	Object* instance_list;
	int num_instances;
} Room;

Room* room_get();
void room_set();
void room_execute_event(int event, ...);

#endif