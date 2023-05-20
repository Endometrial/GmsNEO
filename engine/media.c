#include <engine/media.h>

char* file_load_string(char* filepath) {
	FILE* fptr;
	char* string;
	long size;

	// Open the file
	if (!(fptr = fopen(filepath, "r"))) {
		printf("Cannot open %s!\n", filepath);
		exit(-1);
	}
	
	//Seek towards the end
	if (fseek(fptr,0L,SEEK_END) != 0) {
		printf("Could not seek %s!\n", filepath);
		fclose(fptr);
		exit(-1);
	}
	
	// Report the length and reset the position of the file pointer
	size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);	

	// Allocate a buffer
	string = malloc((size+1) * sizeof(char));
	
	// Read the file into the buffer
	fread(string, sizeof(char), size, fptr);		
	string[size++] = '\0';
	
	// Check if the process worked
	if (ferror(fptr)) {
		printf("Failed to read %s!\n", filepath);
		fclose(fptr);
		exit(-1);
	}

	// Cleanup
	fclose(fptr);

	return string;
}

Image image_load(char* filepath) {
	Image image;
	FILE* img_fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep* row_ptrs;

	img_fp = fopen(filepath, "rb");
	if (!img_fp) {
		printf("Cannot open image :(");
		fclose(img_fp);
		exit(1);
	}
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);

	if (!(png_ptr && (info_ptr && !setjmp(png_jmpbuf(png_ptr))))) {
		printf("Libpng data failed to initialize :(");
		png_destroy_read_struct(&png_ptr, &info_ptr, &info_ptr);
		fclose(img_fp);
		exit(1);
	}

	png_init_io(png_ptr, img_fp);
	png_read_info(png_ptr, info_ptr);
	// Read image data from 8 byte header
	png_get_IHDR(png_ptr, info_ptr, &image.width, &image.height, &image.bit_depth, &image.color_type, 0, 0, 0);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) || (image.color_type == PNG_COLOR_TYPE_GRAY && image.bit_depth < 8) || image.color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png_ptr);
	if (image.bit_depth == 16) 
		png_set_strip_16(png_ptr);
	if (image.color_type == PNG_COLOR_TYPE_GRAY || image.color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	// Reset info ptr
	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	rowbytes += 3 - ((rowbytes-1) % 4); // Make a multiple of 4

	image.data = malloc(rowbytes * image.height * sizeof(png_byte) + 15);
	if (!image.data) {
		printf("Failed to allocate bytes :(");
		png_destroy_read_struct(&png_ptr, &info_ptr, &info_ptr);
		fclose(img_fp);
		exit(1);
	}

	row_ptrs = malloc(image.height * sizeof(png_bytep));

	// Set each pointer to point to a part of data
	for (int i=0; i<image.height; i++) {
		row_ptrs[image.height-1-i] = image.data + i*rowbytes;
	}

	png_read_image(png_ptr, row_ptrs);

	png_destroy_read_struct(&png_ptr, &info_ptr, &info_ptr);
	fclose(img_fp);

	return image;
}

GLuint image_load_texture(char* filepath, GLint texture_wrap, GLint texture_filter) {
	Image picture;
	GLuint texture;
	GLenum format;

	picture = image_load(filepath);
	format = (picture.color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, picture.width, picture.height, 0, format, GL_UNSIGNED_BYTE, picture.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter); // for scaling up

	return texture;
}
