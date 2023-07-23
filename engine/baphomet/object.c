#include <baphomet/object.h>

Object asset_load_object(char* filepath) {
	Object object;

	object.handle = dlopen(filepath, RTLD_NOW);
	(object.handle == NULL) ? fprintf(stderr, "asset_load_object(): %s\n", dlerror()) : 1;

	object.create = dlsym(object.handle, "create");
	object.step = dlsym(object.handle, "step");
	object.draw = dlsym(object.handle, "draw");
	object.destroy = dlsym(object.handle, "destroy");
	object.cleanup = dlsym(object.handle, "cleanup");

	return object;
}

void asset_unload_object(Object* object) {
	object->cleanup();
	object->destroy();
	(dlclose(object->handle)) ? fprintf(stderr, "asset_unload_object(): %s\n", dlerror()) : 1;
}

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

