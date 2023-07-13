#include <baphomet/room.h>

Room current_room;

Room room_get() {
	return current_room;
}

void room_set(Room room) {
	current_room = room;
}

void room_execute_event(int event, ...) {
	va_list parameters;
	for (unsigned int i=0; i<current_room.num_instances; i++) {
		double program_time, delta_time;
		switch(event) {
			case EVENT_CREATE:
				current_room.instance_list[i].create();
				break;
			case EVENT_STEP:
				va_start(parameters, event);
				program_time = va_arg(parameters, double); // I know...
				delta_time = va_arg(parameters, double); // It wouldnt let me without assigning :(
				current_room.instance_list[i].step(program_time, delta_time);
				va_end(parameters);
				break;
			case EVENT_DRAW:
				va_start(parameters, event);
				program_time = va_arg(parameters, double);
				delta_time = va_arg(parameters, double);
				current_room.instance_list[i].draw(program_time, delta_time);
				va_end(parameters);
				break;
			case EVENT_CLEANUP:
				current_room.instance_list[i].cleanup();
				break;
			default:
				printf("Invalid event! Ao says room.c! x3");
				exit(-1);
		}
	}
}