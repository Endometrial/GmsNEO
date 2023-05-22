
#include <engine/room.h>

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

Room room_load(char* filepath) {
	Room room;
	Object* instance_list;
	xmlParserCtxtPtr context_ptr;
	xmlDocPtr doc;
	xmlNodePtr current_node;
	int num_instances = 0;

	instance_list = malloc(sizeof(Object));

	doc = xmlParseFile(filepath);
	if (doc == NULL) {
		printf("%s could not be parsed successfully :<\n",filepath);
		xmlFreeDoc(doc);
		exit(-1);
	}

	// <room>
	current_node = xmlDocGetRootElement(doc);
	if (doc == NULL) {
		printf("%s appears to be empty? :O\n",filepath);
		xmlFreeDoc(doc);
		exit(-1);
	}

	// <background> <instance>
	current_node = current_node->xmlChildrenNode;
	while (current_node != NULL) {
		if (current_node->type == XML_ELEMENT_NODE) {
			switch(current_node->name[0]) {
				case 'b': //background (ptrs don work w switch)
					printf("Backgrounds not yet supported :(\n");
					break;
				case 'i': //instance
					xmlAttr* attributes;
					xmlNodePtr instance_node = current_node;
					current_node = instance_node->xmlChildrenNode;
					
					// <object> <priority> <location> <script>
					for (1; current_node!=NULL; current_node = current_node->next) {
						if (current_node->type == XML_ELEMENT_NODE) {
							switch(current_node->name[0]) {
								case 'o': // object
										instance_list[num_instances] = object_load(xmlNodeGetContent(current_node));
										num_instances++;
										instance_list = realloc(instance_list, (num_instances+1) * sizeof(Object));
									break;
								case 'l': // location
										// idk how im gonna do this man ;w;
									break;
								case 's': // script
										char* script_filepath = xmlNodeGetContent(current_node);
										// idk how im gonna do this man ;w;
									break;
								default:
									printf("dafuq is a %s ??????\n", current_node->name);
							}
						}
					}

					current_node = instance_node;
					break;
				default:
					printf("%s contains an illegal node >:3. wtf r u trying to pull lmao?\n", filepath); 
			}
		}
		current_node = current_node->next;
	}

	room.filepath = filepath;
	room.instance_list = instance_list;
	room.num_instances = num_instances;

	return room;
}

void room_unload(Room room) {
	free(room.instance_list);
}