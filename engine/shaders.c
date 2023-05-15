
#include <engine/shader.h>

unsigned int shader_build(char* filepath, int type) {
	unsigned int shader;
	GLchar* shaderSource;
	int success;
	char infoLog[512];

	// Load the shader into a buffer
	shaderSource = file_load_string(filepath);

	// Create and compile the shader
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	// Free the buffer
	free(shaderSource);

	// Check if the process worked
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("%s : FAILED TO COMPILE : %s\n", filepath, infoLog);
		return -1;
	}

	return shader;
}

unsigned int shader_program_create(unsigned int shader, ...) {
	unsigned int program;
	va_list shaderArgs;
	int success;
	char infoLog[512];

	// Create the program
	program = glCreateProgram();


	// Attach shaders to the program
	va_start(shaderArgs, shader);
	for (unsigned int i = shader; i > 0; i = va_arg(shaderArgs, int)) {
		glAttachShader(program, i);
	}
	va_end(shaderArgs);

	// Link the program
	glLinkProgram(program);

	// Check if the process worked
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("FAILED TO LINK : %s\n", infoLog);
		return -1;
	}

	// Cleanupe
	va_start(shaderArgs, shader);
	for (unsigned int i = shader; i > 0; i = va_arg(shaderArgs, int)) {
		glDeleteShader(i);
	}
	va_end(shaderArgs);

	return program;
}

void shader_program_apply(unsigned int program) {
	glUseProgram(program);
}

void shader_set_uniform_vec4(unsigned int program, char* name, float x, float y, float z, float w) {
	int location;
	location = glGetUniformLocation(program, name);
	glUniform4f(location, x, y, z, w);
}

void shader_set_uniform_float(unsigned int program, char* name, float val) {
	int location;
	location = glGetUniformLocation(program, name);
	glUniform1f(location, val);
}

void shader_set_uniform_int(unsigned int program, char* name, int val) {
	int location;
	location = glGetUniformLocation(program, name);
	glUniform1i(location, val);
}

void shader_set_uniform_mat4(unsigned int program, char* name, float* matrix) {
	int location;
	location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}
