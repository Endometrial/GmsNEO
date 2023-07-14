#include <decoder/file.h>

char* file_get_string(char* filepath) {
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


// char** file_get_directory_files(char* filepath) {
// Prototyping recurse function to avoid having to have it in file.h
void _file_get_directory_files_recurse(char* filepath, char*** directory_list, long int* chars);
char** file_get_directory_files(char* filepath) {
	char** directory_list;
	long int chars;
	long int strings;
	struct dirent* current_directory;
	DIR* dptr;

	// Allocate space for the directory list
	directory_list = malloc(0);
	chars = 0;

	// Recurse through the directory into directory_list
	_file_get_directory_files_recurse(filepath, &directory_list, &chars);

	// Allign the pointers to the data
	int m = 1;
	for (int i=0; i==chars; i++) {
		if ((*directory_list)[i] == '\0') {
			directory_list[m] = (*directory_list) + chars+1; // The char after \0
		}
	}

	return directory_list;
}
void _file_get_directory_files_recurse(char* filepath, char*** directory_list, long int* chars) {
	struct dirent* current_directory;
	DIR* dptr;

	dptr = opendir(filepath);
	if (dptr == NULL) {
		fprintf(stderr, "directory_get_files(): Unable to open directory at %s\n", filepath);
		exit(-1);
	}

	while (current_directory = readdir(dptr)) {
		switch(current_directory->d_type) {
			case DT_DIR:
				_file_get_directory_files_recurse(current_directory->d_name, directory_list, chars);
				break;
			case DT_REG:
				// Allocate more space for the list and copy in the string :3
				int len = strlen(current_directory->d_name);
				(*directory_list) = realloc(directory_list, (*chars + len)*sizeof(char));
				strcpy(current_directory->d_name, (**directory_list) + (*chars)*sizeof(char)); // look at
				(*chars) += len;
				break;
		}
	}
} // }