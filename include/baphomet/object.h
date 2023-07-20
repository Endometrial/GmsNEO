#ifndef BAPHOMET_OBJECT_H
#define BAPHOMET_OBJECT_H

/*
	Object.h
	Created: xxxx-xx-xx
	Description:
		Object.h is a catchall for object manipulation
		with the exception of object loading. wow! dlfcn
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <baphomet/tools.h>

#define EVENT_CREATE 0
#define EVENT_STEP 1
#define EVENT_DRAW 2
#define EVENT_CLEANUP 3
#define EVENT_DESTROY 4

typedef struct {
	void* handle;
	void (*create)();
	void (*step)(double program_time, double delta_time);
	void (*draw)(double program_time, double delta_time);
	void (*destroy)();
	void (*cleanup)();
} Object;

void* object_get_uniform(Object* object, char* symbol_name);
void object_set_uniform_double(Object* object, char* symbol_name, double value);
void object_set_uniform_object_id(Object* object, char* symbol_name);

#endif