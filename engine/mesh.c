#include <engine/mesh.h>

/*
// vbo = data
// ebo = pointers to the above
// vao = array of the above
unsigned int mesh_generate(unsigned int mode, float** vertices, size_t* vertsizeof, float** indices, size_t* indisizeof) {
	unsigned int vao, vertnum, indinum;
	unsigned int* vbo, ebo;

	numverts = vertsizeof/sizeof(void*);
	numindis = indisizeof/sizeof(void*);

	glGenVertexArrays(1, &vao);
	glGenBuffers(numverts, vbo);
	glGenBuffers(numindis, ebo);

	glBindVertexArray(vao);
	for (int i=0; i<numverts; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], mode);}
	for (int i=0; i<numindis; i++) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[i]), indices[i], mode);}

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
	//glEnableVertexAttribArray(0);

	return vao;
}*/

//mesh_add_vertices(unsigned int vao);
/*
unsigned int mesh_initialize() {
	unsigned int vao, vertsize, indisize;
	unsigned int vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, vertsizeof, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indisizeof, indices, GL_STATIC_DRAW);

	return vao;
}*/

Mesh mesh_initialize() {
	Mesh mesh;

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	mesh.elements = 0;

	return mesh;
}

Mesh mesh_add_vertices(Mesh mesh, GLenum mode, float* vertices, size_t size) {
	unsigned int vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, mode);

	mesh.elements = size / sizeof(float);

	return mesh;
}

Mesh mesh_add_indexed_vertices(Mesh mesh, GLenum mode, float* vertices, size_t sizev, unsigned int* indices, size_t sizei) {
	unsigned int vbo, ebo;

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizev, vertices, mode);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizei, indices, mode);

	mesh.elements = sizei / sizeof(unsigned int);

	return mesh;
}

void mesh_build() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL);
	glEnableVertexAttribArray(0);
}

		/*
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// NOTE: &VAO, etc... can be substituted with a list of pointers

	glBindVertexArray(VAO); // This is first
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Stream = static used a few times
	// Static = static used many times
	// Dynamic = mutable and used many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);*/
