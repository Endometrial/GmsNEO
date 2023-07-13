#include <baphomet/texture.h>
/*
int texture_get_bit_depth(Texture* texture) {
	void* user_data = texture->user_data;
	switch(texture->type) {
		case IMG_TYPE_PNG:
			return png_get_bit_depth((PngDecoder*)user_data);
			break;
		default:
			fprintf(stderr, "texture_get_bit_depth(): Texture is of unknown type");
			exit(-1);
	}
}


int texture_get_color_type(Texture texture) {
	int color_type;
	switch(texture.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = texture.user_data;
			color_type = png_get_color_type(decoder);
			break;
		default:
			fprintf(stderr, "texture_get_color_type(): Texture is of unknown type");
			exit(-1);
	}
	return color_type;
}

unsigned int texture_get_width(Texture texture) {
	unsigned int width;
	switch(texture.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = texture.user_data;
			width = png_get_width(decoder);
			break;
		default:
			fprintf(stderr, "texture_get_width(): Texture is of unknown type");
			exit(-1);
	}
	return width;
}
*/
unsigned int texture_get_height(Texture texture) {
	unsigned int height;
	switch(texture.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = texture.user_data;
			height = png_decoder_get_height(decoder);
			break;
		default:
			fprintf(stderr, "texture_get_height(): Texture is of unknown type");
			exit(-1);
	}
	return height;
}
