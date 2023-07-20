#ifndef BAPHOMET_FILE_H
#define BAPHOMET_FILE_H

/*
	File.h
	Created: xxxx-xx-xx
	Description:
		File.h is a catchall for filesystem manipulation
		and text file manipulation
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// This file will hopefully be replaced by a smarter solution eventually ;w;

char* file_get_string(char* filepath);
char** file_get_directory_files(char* filepath);

#endif