#ifndef OBJECT_H
#define OBJECT_H

#include <dlfcn.h>
#include <stdio.h>

typedef struct {
	void* handle;
	void (*create)();
	void (*step)(double program_time, double delta_time);
	void (*draw)(double program_time, double delta_time);
	void (*cleanup)();
	void (*destroy)();
} Object;

Object object_load(char* library_filepath);

#endif