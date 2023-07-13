#ifndef BAPHOMET_ROOM_H
#define BAPHOMET_ROOM_H

#include <stdlib.h>
#include <libxml/parser.h>

#include <baphomet/object.h>

typedef struct {
	Object* instance_list;
	int num_instances;
} Room;

Room room_get();
void room_set();
void room_execute_event(int event, ...);

#endif