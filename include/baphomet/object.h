#ifndef BAPHOMET_OBJECT_H
#define BAPHOMET_OBJECT_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

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

Object object_load(char* library_filepath);

#endif