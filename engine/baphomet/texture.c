#include <baphomet/texture.h>

Texture asset_load_texture(char* filepath) {
	int format, height, width;
	unsigned char* data;
	Texture texture;

	// Check the file type
	//sprite.type = (png_decoder_is_png(filepath)) ? IMG_TYPE_PNG : IMG_TYPE_UNKNOWN;
	texture.type = IMG_TYPE_PNG;

	// Generate a texture
	glGenTextures(1, &texture.texture);
	glBindTexture(GL_TEXTURE_2D, texture.texture);

	// Switch over the filetype to extract data
	switch(texture.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = png_decoder_open(filepath);
			texture.user_data = decoder;
			data = png_decoder_get_data(decoder);
			width = png_decoder_get_width(decoder);
			height = png_decoder_get_height(decoder);
			format = (png_decoder_get_color_type(decoder) & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			png_decoder_free_data(data); // Free the data as it is no longer needed
			break;
		default:
			// Report that no filetype could be matched & exit
			fprintf(stderr, "asset_load_sprite(): file provided was not of a supported type!\n");
			fprintf(stderr, "	supported types include : ");
			for (int i=0; supported_image_filetypes[i] != NULL; i++) {
				fprintf(stderr, "%s ", supported_image_filetypes[i]);}
			fprintf(stderr, "\n");
			exit(-1);
			break;
	}

	// Set variables (will be made obsolete in the future (ex sprite.c))
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, DEFAULT_TEXTURE_WRAP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, DEFAULT_TEXTURE_WRAP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DEFAULT_TEXTURE_FILTER); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DEFAULT_TEXTURE_FILTER); // for scaling up

	// This is pretty so im leaving it even though its useless now. fuck off ;3 <3
	//float ratio = (float)height / (float)width;
	//sprite.mesh = (ratio>1.0f) ? mesh_generate_rect(1.0f/ratio, 1.0f) : mesh_generate_rect(1.0f, 1.0f*ratio);
	//sprite.mesh = mesh_generate_rect(0.0f,0.0f,(float)width, (float)height, 0.0f);

	// Free data plz ;w;
	return texture;}

void asset_unload_texture(Texture* texture) {

	// Delete textures
	glDeleteTextures(1, &texture->texture);

	// Delete the mesh

	// Delete whatever is contained within user data
	switch(texture->type) {
		case IMG_TYPE_PNG:
			png_decoder_close(texture->user_data);
			break;
		default:
			fprintf(stderr, "asset_unload_sprite(): Unknown filetype!\n");
			break;
	}
}

int texture_get_bit_depth(Texture* texture) {
	void* user_data = texture->user_data;
	switch(texture->type) {
		case IMG_TYPE_PNG:
			return png_decoder_get_bit_depth((PngDecoder*)user_data);
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
			color_type = png_decoder_get_color_type(decoder);
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
			width = png_decoder_get_width(decoder);
			break;
		default:
			fprintf(stderr, "texture_get_width(): Texture is of unknown type");
			exit(-1);
	}
	return width;
}

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
