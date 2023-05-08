#include <engine/media.h>

char* file_load_string(char* filepath) {
	FILE* fptr;
	char* string;
	long size;

	// Open the file
	if (!(fptr = fopen(filepath, "r"))) {
		printf("Cannot open file!");
		return -1;
	}
	
	//Seek towards the end
	if (fseek(fptr,0L,SEEK_END) != 0) {
		printf("File could not be read!");
		fclose(fptr);
		return -1;
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
		printf("Failed to read file!");
		fclose(fptr);
		return -1;
	}

	// Cleanup
	fclose(fptr);

	return string;
}
/*
unsigned char* image_load_data(char* filepath, int width, int height, int channels) {
	unsigned char* data;
	data = stbi_load(filepath, &width, &height, &channels, 0);
}
*/