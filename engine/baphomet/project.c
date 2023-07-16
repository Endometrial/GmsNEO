#include <baphomet/project.h>

Project* project; // There is only one project

void project_open_xml(char* filepath) {
	XmlDecoder* decoder;
	XmlNode* current_node;
	int project_strlen;

	// Load the xml
	decoder = xml_decoder_open(filepath);

	// Allocate space for the project struct
	project = malloc(sizeof(Project));
	project_strlen = 0;

	// Place the required data into the project struct
	current_node = xml_node_get_children(xml_decoder_get_root_node(decoder));
	for (1; current_node!=NULL; current_node=current_node->next) {
		if (xml_node_is_element_node(current_node)) {
			switch(xml_node_get_name(current_node)[0]) {
				case 'n': // <name>
					project_strlen += strlen(xml_node_get_content(current_node));
					project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
					project->name = xml_node_get_content(current_node);
					break;
				case 'r': // <room>
					project_strlen += strlen(xml_node_get_content(current_node));
					project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
					project->room = xml_node_get_content(current_node);
					break;
				case 'd': // <directory>
					XmlNode* directory_node = xml_node_get_children(current_node);
					for (1; directory_node!=NULL; directory_node=directory_node->next) {
						if (xml_node_is_element_node(directory_node)) {
							switch(xml_node_get_name(directory_node)[0]) {
								case 'o': // <directory> -> <object>
									project_strlen += strlen(xml_node_get_content(directory_node));
									project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
									project->object_directory = xml_node_get_content(directory_node);
									break;
								case 'r': // <directory> -> <room>
									project_strlen += strlen(xml_node_get_content(directory_node));
									project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
									project->room_directory = xml_node_get_content(directory_node);
									break;
								default:
									fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(directory_node));
									break;
							}
						}
					}
					break;
				case 'w': // <window>
					XmlNode* window_node = xml_node_get_children(current_node);
					for (1; window_node!=NULL; window_node=window_node->next) {
						if (xml_node_is_element_node(window_node)) {
							switch(xml_node_get_name(window_node)[0]) {
								case 'n': // <window> -> <name>
									project_strlen += strlen(xml_node_get_content(window_node));
									project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
									project->window_name = xml_node_get_content(window_node);
									break;
								case 's': // <window> -> <size>
									project->width = strtoumax(xml_node_get_attribute(window_node, "width"), NULL, 10);
									project->height = strtoumax(xml_node_get_attribute(window_node, "height"), NULL, 10);
									break;
								case 'c': // <window> -> <callback>
									project->framebuffer_callback = strtoimax(xml_node_get_attribute(window_node, "callback"), NULL, 16);
									break;
								case 'v': // <window> -> <vsh>
									project_strlen += strlen(xml_node_get_content(window_node));
									project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
									project->vsh = xml_node_get_content(window_node);
									break;
								case 'f': // <window> -> <fsh>
									project_strlen += strlen(xml_node_get_content(window_node));
									project = realloc(project, sizeof(Project) + project_strlen*sizeof(char));
									project->fsh = xml_node_get_content(window_node);
									break;
								case 'b': // <window> -> <blend>
									project->sfactor_blendmode = strtoimax(xml_node_get_attribute(window_node, "sfactor"), NULL, 16);
									project->dfactor_blendmode = strtoimax(xml_node_get_attribute(window_node, "dfactor"), NULL, 16);
									break;
								default:
									fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(window_node));
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
	}
	xml_decoder_close(decoder);
}

void project_close() {
	free(project);
}

char* project_get_name() {
	return project->name;}

char* project_get_default_window_name() {
	return project->window_name;}

char* project_get_default_room_filepath() {
	return project->room;}

char* project_get_default_vertex_shader_filepath() {
	return project->vsh;}

char* project_get_default_fragment_shader_filepath() {
	return project->fsh;}

unsigned int project_get_default_window_width() {
	return project->width;}

unsigned int project_get_default_window_height() {
	return project->height;}

int project_get_default_framebuffer_callback() {
	return project->framebuffer_callback;}

int project_get_default_dfactor_blendmode() {
	return project->dfactor_blendmode;}

int project_get_default_sfactor_blendmode() {
	return project->sfactor_blendmode;}

char* project_get_default_object_directory() {
	return project->object_directory;}

char* project_get_default_room_directory() {
	return project->room_directory;}
