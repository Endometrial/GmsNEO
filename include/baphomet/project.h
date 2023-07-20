#ifndef BAPHOMET_PROJECT_H
#define BAPHOMET_PROJECT_H

/*
	Project.h
	Created: xxxx-xx-xx
	Description:
		Project.h is a bulky catchall for project
		manipulation and may soon come to help
		window.h with their midlife crisis
*/

#include <stdio.h>
#include <inttypes.h>
#include <baphomet/draw.h> // For blend modes
#include <baphomet/window.h> // For framebuffer callbacks
#include <decoder/xml.h>

typedef struct {
	char* name;
	char* window_name;
	char* room;
	char* vsh;
	char* fsh;
	unsigned int width;
	unsigned int height;
	int framebuffer_callback;
	int dfactor_blendmode;
	int sfactor_blendmode;
	char* object_directory;
	char* room_directory;
} Project;

void project_open_xml(char* filepath);
void project_close();

char* project_get_name();
char* project_get_default_window_name();
char* project_get_default_room_filepath();
char* project_get_default_vertex_shader_filepath();
char* project_get_default_fragment_shader_filepath();
unsigned int project_get_default_window_width();
unsigned int project_get_default_window_height();
int project_get_default_framebuffer_callback();
int project_get_default_dfactor_blendmode();
int project_get_default_sfactor_blendmode();
char* project_get_default_object_directory();
char* project_get_default_room_directory();

#endif