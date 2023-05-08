#ifndef MEDIA_H
#define MEDIA_H

#include <stdio.h>
#include <stdlib.h>

char* file_load_string(char* filepath);
unsigned char* image_load_data(char* filepath, int width, int height, int channels);

#endif
