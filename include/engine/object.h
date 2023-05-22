#ifndef OBJECT_H
#define OBJECT_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void* handle;
	void (*create)();
	void (*step)(double program_time, double delta_time);
	void (*draw)(double program_time, double delta_time);
	void (*destroy)();
	void (*cleanup)();
	long id;
} Object;

Object object_load(char* library_filepath);

#endif