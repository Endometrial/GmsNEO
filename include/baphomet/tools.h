#ifndef BAPHOMET_TOOLS_H
#define BAPHOMET_TOOLS_H

/*
	Tools.h
	Created: 2023-07-18
	Description:
		Tools.h is a catchall for anything small im
		not sure should be given its own file.
		most likely its days are numbered (like draw.h)
		(likely will have file.h merged into it if kept)
		Currently includes:
			* Regex functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>
#include <string.h>

int regex_evaluate_string(char* regex, char* string);
char* regex_get_substring(char* regex, char* string);
void regex_free_substring(char* substring);


#endif