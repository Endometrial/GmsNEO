#include <baphomet/room.h>

Room current_room;

Room asset_load_room(char* filepath) {
	Room room;
	XmlDecoder* decoder; // There is only one kind of room
	xmlNode* current_node;

	// Allocate space for the room instance list
	room.instance_list = malloc(0);
	room.num_instances = 0;

	// Load the xml
	decoder = xml_decoder_open(filepath);

	// Loading <background> <instance>
	current_node = xml_node_get_children(xml_decoder_get_root_node(decoder));
	while (current_node != NULL) {
		if (xml_node_is_element_node(current_node)) {
			switch(xml_node_get_name(current_node)[0]) {
				case 'b': // <background>
					fprintf(stderr, "asset_load_room(): Backgrounds are not yet supported\n");
					break;
				case 'o': // <object>
					// Load the instance from <instance name="">
					room.num_instances++;
					room.instance_list = realloc(room.instance_list, room.num_instances*sizeof(Object));
					room.instance_list[room.num_instances-1] = asset_load_object(xml_node_get_attribute(current_node,"name"));

					xmlNode* instance_node = xml_node_get_children(current_node);
					for (1; instance_node!=NULL; instance_node=instance_node->next) {
						if (xml_node_is_element_node(instance_node)) {
							switch(xml_node_get_name(instance_node)[0]) {
								case 'u': // <object> <uniforms>
									for (int i=0;i<xml_node_get_num_attributes(instance_node);i++) {
										char* name = xml_node_get_attribute_name(instance_node, i);
										void* uniform = object_get_uniform(&(room.instance_list[room.num_instances-1]), name);

										// Loop through supported regeges
										char* l[]={long_int_textformat_regex, double_float_textformat_regex, binary_int_textformat_regex, hexedecimal_int_textformat_regex, hexedecimal_pointer_textformat_regex, NULL};
										for (int i=0; l[i]!=NULL; i++) {
											char* substring = regex_get_substring(l[i], xml_node_get_attribute(instance_node, name));
											if (substring != NULL) {
												switch(i) {
													case 0: // LONG_REGEX
														*((long*)uniform)	= strtol(substring,NULL,10);
														break;
													case 1: // DOUBLE_REGEX
														*((double*)uniform) = strtod(substring, NULL);
														break;
													case 2: // BINARY_REGEX
														*((long*)uniform) 	= strtol(substring,NULL,2);
														break;
													case 3: // HEXEDECIMAL_REGEX
														*((long*)uniform) 	= strtol(substring,NULL,16);
														break;
													case 4: // HEXPTR_REGEX
														*((void**)uniform)	= (void*)strtol(substring,NULL,16);
														break;
													default: // STRING
														*((char**)uniform) 	= substring;
														break;
												}
												break;
											}
										}
									}
									break;
								default:
									fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(instance_node));
									break;
							}
						}
					}

					break;
				default:
					fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(current_node));
					break;
			}
		}
		current_node = current_node->next; // Advance the node
	}

	// Free data and return the room :)
	xml_decoder_close(decoder);
	return room;
}

void asset_unload_room(Room* room) {
	free(room->instance_list);
}

Room* room_get() {
	return &current_room;
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
			case EVENT_DESTROY:
				current_room.instance_list[i].destroy();
				break;
			default:
				printf("Invalid event! Ao says room.c! x3");
				exit(-1);
		}
	}
}