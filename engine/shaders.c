
#include <engine/shader.h>

Shader shader_create(char* vsh_filepath, char* fsh_filepath) {
	char infoLog[512];
	int success;
	Shader shader;
	
	shader.shader = malloc(sizeof(unsigned int) * SHADER_NUM);
	
	shader.shader[VERTEX_SHADER] = (!vsh_filepath) ? -1 : shader_build_type(vsh_filepath, GL_VERTEX_SHADER);
	shader.shader[FRAGMENT_SHADER] = (!fsh_filepath) ? -1 : shader_build_type(fsh_filepath, GL_FRAGMENT_SHADER);

	shader.program = glCreateProgram();

	for (int i=0; i<SHADER_NUM; i++) {
		(!shader.shader[i]) ? 1 : glAttachShader(shader.program, shader.shader[i]);
	}

	glLinkProgram(shader.program);

	glGetProgramiv(shader.program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader.program, 512, NULL, infoLog);
		printf("FAILED TO LINK : %s\n", infoLog);
	}

	for (int i=0; i<SHADER_NUM; i++) {
		(!shader.shader[i]) ? 1 : glDeleteShader(shader.shader[i]);
	}

	return shader;
}


unsigned int shader_build_type(char* filepath, int type) {
	unsigned int shader;
	GLchar* shaderSource;
	int success;
	char infoLog[512];
	
	// Load the shader into a buffer
	shaderSource = file_load(filepath);

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

void shader_set_uniform_vec4(Shader shader, char* name, float x, float y, float z, float w) {
	int location;
	location = glGetUniformLocation(shader.program, name);
	glUniform4f(location, x, y, z, w);
}

void shader_set_uniform_float(Shader shader, char* name, float val) {
	int location;
	location = glGetUniformLocation(shader.program, name);
	glUniform1f(location, val);
}

void shader_set_uniform_int(Shader shader, char* name, int val) {
	int location;
	location = glGetUniformLocation(shader.program, name);
	glUniform1i(location, val);
}

void shader_set_uniform_mat4(Shader shader, char* name, mat4 matrix) {
	int location;
	location = glGetUniformLocation(shader.program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}
