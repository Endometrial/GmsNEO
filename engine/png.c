#include <engine/png.h>

PngDecoder* png_decoder_open(char* filepath) {
	int bit_depth, color_type;
	PngDecoder* decoder;

	// Allocate some data for the decoder struct
	decoder = malloc(sizeof(PngDecoder));

	decoder->filepointer = fopen(filepath, "rb");
	if (!decoder->filepointer) {
		fprintf(stderr, "png_decoder_open(): Couldnt open %s\n", filepath);
		fclose(decoder->filepointer);
		exit(1);
	}

	// Populate data types
	decoder->state = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	decoder->info  = png_create_info_struct(decoder->state);

	if (!(decoder->state && (decoder->info && !setjmp(png_jmpbuf(decoder->state))))) {
		fprintf(stderr, "png_decoder_open(): Failed to initialize libpng data types in\n");
		png_decoder_close(decoder);
		exit(1);
	}

	// Initialize libpng io
	png_init_io(decoder->state, decoder->filepointer);
	png_read_info(decoder->state, decoder->info);

	// Execute variable functions based on bit_depth, color_type, and "validity"
	bit_depth = png_decoder_get_bit_depth(decoder);
	color_type = png_decoder_get_color_type(decoder);
	if (png_get_valid(decoder->state, decoder->info, PNG_INFO_tRNS) || (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) || color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(decoder->state);
	if (bit_depth == 16) 
		png_set_strip_16(decoder->state);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(decoder->state);

	// Read updated info into infoptr
	png_read_update_info(decoder->state, decoder->info);

	return decoder;}

unsigned char* png_decoder_get_data(PngDecoder* decoder) {
	unsigned char* data;
	int height;
	
	// Prepare data types to be read into by libpng
	height = png_decoder_get_height(decoder);
	int rowbytes = png_get_rowbytes(decoder->state, decoder->info);
	rowbytes += 3 - ((rowbytes-1) % 4); // Make into a multiple of 4

	// Allocate space for data
	png_bytep* row_ptrs;
	row_ptrs = malloc(height * sizeof(png_byte*));
	data = malloc(rowbytes * height * (sizeof(png_byte) + 15));
	if ((!data) || (!row_ptrs)) {
		fprintf(stderr, "png_decoder_populate(): Failed to allocate data");
		png_decoder_close(decoder);
		exit(1);
	}

	// Allign pointers
	for (int i=0; i<height; i++) {
		row_ptrs[height-1-i] = data + i*rowbytes;
	}

	// Read the image
	png_read_image(decoder->state, row_ptrs);

	// Free certain data types and return
	free(row_ptrs);
	return data;}

void png_decoder_free_data(unsigned char* data) {
	free(data);}

void png_decoder_close(PngDecoder* decoder) {
	png_destroy_read_struct(&decoder->state, &decoder->info, &decoder->info);
	fclose(decoder->filepointer);
	free(decoder);}

int png_decoder_is_png(char* filepath) {
	// Open the file
	FILE* fptr = fopen(filepath, "rb");
	if (!fptr) {
		fprintf(stderr, "png_decoder_is_png(): Couldnt open %s\n", filepath);
		fclose(fptr);
		exit(1);
	}
	// Read the first 8 bytes into a buffer (which is then made into a int64)
	unsigned char* buffer = malloc(8 * sizeof(unsigned char));
	int len = fwrite(buffer, sizeof(png_byte), 8, fptr);
	if (len < 8) {
		fprintf(stderr,"png_decoder_is_png(): Premature EOF. Almost certainly is not png (but im not going to stop you >;3)");
		return 0;
	}
	int64_t header = 0;
	for (int i=0; i<8; i++) {
		// I am aware that there are issues with this method; However, it requires i read about endian byte orders.
		// and frankly I would rather jump off a bridge (jk just tired haha. dont call the cops on me lolz)
		header += (buffer[i])<<(i<<1);
	}
	// cleanup and return the comparison
	rewind(fptr);
	fclose(fptr);
	return (header == PNG_8BYTE_HEADER);}

int png_decoder_get_bit_depth(PngDecoder* decoder) {
	int bit_depth;
	png_get_IHDR(decoder->state, decoder->info, NULL, NULL, &bit_depth, NULL, NULL, NULL, NULL);
	return bit_depth;}

int png_decoder_get_color_type(PngDecoder* decoder) {
	int color_type;
	png_get_IHDR(decoder->state, decoder->info, NULL, NULL, NULL, &color_type, NULL, NULL, NULL);
	return color_type;}

unsigned int png_decoder_get_width(PngDecoder* decoder) {
	int width;
	png_get_IHDR(decoder->state, decoder->info, &width, NULL, NULL, NULL, NULL, NULL, NULL);
	return width;}

unsigned int png_decoder_get_height(PngDecoder* decoder) {
	int height;
	png_get_IHDR(decoder->state, decoder->info, NULL, &height, NULL, NULL, NULL, NULL, NULL);
	return height;}