
#include <engine/object.h>

Object object_load(char* library_filepath) {
	Object object;

	object.handle = dlopen(library_filepath, RTLD_NOW);

	if (object.handle == NULL) {
		printf("Unable to open object: %s\n", dlerror());
	}

	object.create = dlsym(object.handle, "create");
	object.step = dlsym(object.handle, "step");
	object.draw = dlsym(object.handle, "draw");
	object.destroy = dlsym(object.handle, "destroy");
	object.cleanup = dlsym(object.handle, "cleanup");

	return object;
}

void object_unload(Object object) {
	object.destroy();
	object.cleanup();
	if (dlclose(object.handle)) {
		printf("Unable to unload: %s\n", dlerror());
	}
}