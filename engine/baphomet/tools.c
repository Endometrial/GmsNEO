#include <baphomet/tools.h>

int regex_evaluate_string(char* regex, char* string) {
	const char* error_msg;
	int error_offset;
	pcre* pcre;
	int err;

	pcre = pcre_compile(regex, 0, &error_msg, &error_offset, NULL);
	if (pcre == NULL) {
		fprintf(stderr, "regex_evaluate_string(): Unable to compile regex \"%s\" failed at [%d]: %s\n", regex, error_offset, error_msg);
		exit(-1);
	}

	err = pcre_exec(pcre, NULL, string, strlen(string), 0, 0, NULL, 0);
	pcre_free(pcre);
	return (!err);}

char* regex_get_substring(char* regex, char* string) {
	const char* error_msg;
	char* substring;
	int error_offset;
	int byte_list[2];
	pcre* pcre;
	int err, offset, length;

	pcre = pcre_compile(regex, 0, &error_msg, &error_offset, NULL);
	if (pcre == NULL) {
		fprintf(stderr, "regex_get_substring(): Unable to compile regex \"%s\" failed at [%d]: %s\n", regex, error_offset, error_msg);
		exit(-1);
	}

	err = pcre_exec(pcre, NULL, string, strlen(string), 0, 0, byte_list, 2);

	offset = byte_list[0];
	length = byte_list[1] - offset;

	substring = malloc(length);
	strncpy(substring, string+offset, length);

	pcre_free(pcre);
	return substring;}

void regex_free_substring(char* substring) {
	free(substring);}