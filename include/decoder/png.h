#ifndef BAPHOMET_PNGDECODER_H
#define BAPHOMET_PNGDECODER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>

#define PNG_8BYTE_HEADER 0x89504E470D0A1A0A

typedef struct {
	FILE*		filepointer;
	png_structp	state;
	png_infop	info;
} PngDecoder;

int png_decoder_is_png(char* filepath);
PngDecoder* png_decoder_open(char* filepath);
unsigned char* png_decoder_get_data(PngDecoder* decoder);
void png_decoder_free_data(unsigned char* data);
void png_decoder_close(PngDecoder* decoder);
int png_decoder_get_bit_depth(PngDecoder* decoder);
int png_decoder_get_color_type(PngDecoder* decoder);
unsigned int png_decoder_get_width(PngDecoder* decoder);
unsigned int png_decoder_get_height(PngDecoder* decoder);


#endif