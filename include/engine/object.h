#ifndef OBJECT_H
#define OBJECT_H

#include <dlfcn.h>
#include <stdio.h>

typedef struct {
	void* handle;
	void (*create)();
	void (*step)();
	void (*draw)();
	void (*cleanup)();
	void (*destroy)();
} Object;

Object object_load(char* library_filepath);

#endif