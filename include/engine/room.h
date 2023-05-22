#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>
#include <engine/object.h>
#include <libxml/parser.h>

typedef struct {
	char* filepath;
	Object* instance_list;
	int num_instances;
} Room;

Room room_get();
void room_set();
Room room_load(char* filepath);
void room_execute_event(int event, ...);

#endif