#include <engine/file.h>

char* file_load(char* filepath) {
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
	return string;}