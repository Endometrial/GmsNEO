#include <baphomet/object.h>

void* object_get_uniform(Object* object, char* symbol_name) {
	void* uniform = (void*)dlsym(object->handle, symbol_name);
	if (uniform == NULL) {
		fprintf(stderr, "object_get_uniform(): Couldnt open symbol \"%s\"\n", symbol_name);
		return NULL;
	}
	return uniform;
}

void object_set_uniform_double(Object* object, char* symbol_name, double value) {
	double* uniform = (double*)dlsym(object->handle, symbol_name);
	if (uniform == NULL) {
		fprintf(stderr, "object_set_uniform_double(): Couldnt open symbol \"%s\"\n", symbol_name);
		return;
	}
	(*uniform) = value;
}

void object_set_uniform_object_id(Object* object, char* symbol_name) {
	Object** uniform = (Object**)dlsym(object->handle, symbol_name);
	if (uniform == NULL) {
		fprintf(stderr, "object_set_uniform_object_id(): Couldnt open symbol \"%s\"\n", symbol_name);
		return;
	}
	(*uniform) = object;
}

