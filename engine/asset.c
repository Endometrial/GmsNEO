#include <engine/asset.h>

Sprite asset_load_sprite(char* filepath, GLint texture_wrap, 
	GLint texture_filter) {
	int format, height, width;
	unsigned char* data;
	Sprite sprite;

	// Check the file type
	//sprite.type = (png_decoder_is_png(filepath)) ? IMG_TYPE_PNG : IMG_TYPE_UNKNOWN;
	sprite.type = IMG_TYPE_PNG;

	// Generate a texture
	glGenTextures(1, &sprite.texture);
	glBindTexture(GL_TEXTURE_2D, sprite.texture);

	// Switch over the filetype to extract data
	switch(sprite.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = png_decoder_open(filepath);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter); // for scaling up

	// This is pretty so im leaving it even though its useless now. fuck off ;3 <3
	float ratio = (float)height / (float)width;
	sprite.mesh = (ratio>1.0f) ? mesh_generate_rect(1.0f/ratio, 1.0f) : mesh_generate_rect(1.0f, 1.0f*ratio);
	//sprite.mesh = mesh_generate_rect(0.0f,0.0f,(float)width, (float)height, 0.0f);

	// Free data plz ;w;
	return sprite;}

void asset_unload_sprite(Sprite* sprite) {

	// Delete textures
	glDeleteTextures(1, &sprite->texture);
	
	// Delete the mesh

	// Delete whatever is contained within user data
	switch(sprite->type) {
		case IMG_TYPE_PNG:
			png_decoder_close(sprite->user_data);
			break;
		default:
			fprintf(stderr, "asset_unload_sprite(): Unknown filetype!\n");
			break;
	}
}

Sound asset_load_sound(char* filepath) {
	PaStreamParameters in, out;
	int filetype;
	Sound sound;
	PaError err;

	// Check the filetype
	filetype = (ogg_decoder_is_vorbis(filepath)) ? SND_TYPE_VORBISFILE : SND_TYPE_UNKNOWN;

	// Switch over the possible filetypes & populate struct
	switch(filetype) {
		case SND_TYPE_VORBISFILE:
			OggDecoder* decoder = ogg_decoder_open(filepath);
			sound = audio_create_sound(filetype, ogg_decoder_get_rate(decoder), (void*)decoder);
			break;
		default:
			// Report that no filetype could be matched & exit
			fprintf(stderr, "asset_load_sound(): file provided was not of a supported type!\n");
			fprintf(stderr, "	supported types include : ");
			for (int i=0; supported_audio_filetypes[i] != NULL; i++) {
				fprintf(stderr, "%s ", supported_audio_filetypes[i]);}
			fprintf(stderr, "\n");
			exit(-1);
	}

	return sound;}

void asset_unload_sound(Sound* sound) {
	PaError err;

	switch(sound->type) {
		case SND_TYPE_VORBISFILE:
			ogg_decoder_close(sound->user_data);
		default:
			fprintf(stderr, "asset_unload_sound(): sound type does not exist! why did you do this... well I hope youre doing something interesting. best of luck <3");
			break;
	}

	err = Pa_CloseStream(sound->stream);
	if (err != paNoError) {
		fprintf(stderr, "asset_unload_sound(): Unable to close stream -> %s\n", Pa_GetErrorText(err));
		exit(-1);
	}}