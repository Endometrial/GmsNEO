#include <engine/mesh.h>

Mesh mesh_generate_rect(float width, float height) {
	Mesh mesh;
	float vertices[20] = {
		-width/2,  height/2, 0.0f, 0.0f, 1.0f,
		 width/2,  height/2, 0.0f, 1.0f, 1.0f,
		 width/2, -height/2, 0.0f, 1.0f, 0.0f,
		-width/2, -height/2, 0.0f, 0.0f, 0.0f};
	int indices[6] = {3, 0, 1, 1, 2, 3};
	return mesh_generate_vertices(GL_STATIC_DRAW, DEFAULT_VERTEX_FORMAT, vertices, 20, indices, 6);
}

Mesh mesh_generate_vertices(GLenum mode, int format, float* vertices, int vnum, int* indices, int inum) {
	Mesh mesh = mesh_start(format);
	mesh = mesh_add_vertices(mesh, mode, vertices, vnum, indices, inum);
	mesh_finish(mesh);
	return mesh;
}

Mesh mesh_start(int format) {
	Mesh mesh;

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	mesh.elements = 0;
	mesh.format = format;
	return mesh;
}

void mesh_finish(Mesh mesh) {
	mesh_set_attribute_array(mesh.format);
}

void mesh_set_attribute_array(int format) {

	// Gets the number of each variety of element based on a format of format [XYZUVRGBA]
	int pos_elements, tex_elements, col_elements, index = 0;
	col_elements = !!(format&(1<<0)) + !!(format&(1<<1)) + !!(format&(1<<2)) + !!(format&(1<<3));
	tex_elements = !!(format&(1<<4)) + !!(format&(1<<5));
	pos_elements = !!(format&(1<<6)) + !!(format&(1<<7)) + !!(format&(1<<8));

	// Enable each relevent vertex attribute array
	if (pos_elements) {
		glVertexAttribPointer(index, pos_elements, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
		glEnableVertexAttribArray(index);
		index++;}
	if (tex_elements){
		glVertexAttribPointer(index, tex_elements, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(pos_elements*sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;}
	if (col_elements){
		glVertexAttribPointer(index, col_elements, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)((pos_elements+tex_elements)*sizeof(float)));
		glEnableVertexAttribArray(index);
		index++;}
}

Mesh mesh_add_vertices(Mesh mesh, GLenum mode, float* vertices, size_t velements, int* indices, size_t ielements) {
	unsigned int vbo, ebo;
	int format_elements;

	format_elements = mesh_format_elements(mesh.format);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * velements * format_elements, vertices, mode);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * ielements, indices, mode);

	mesh.elements += ielements;
	return mesh;
}

int mesh_format_elements(int format) {
	int num = 0;
	for (int i=0; i<9; i++) {
		num += !!(format&(1<<i)); // For every bit an addition
	}
	return num;
}
