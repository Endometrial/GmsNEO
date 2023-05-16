#include <engine/mesh.h>

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
/*
Mesh mesh_add_vertices(Mesh mesh, GLenum mode, float* vertices, size_t size) {
	Mesh output_mesh;
	int num_verts, num_inds;
	size_t size_verts, size_inds;
	float* inds, verts; 

	num_verts = (size / VERTEX_ATTRUBUTES / sizeof(float));

	float** vertex;
	for (int j=0;j<VERTEX_ATTRUBUTES;j++) {
		vertex[j] = malloc(sizeof(float));
	}

	size_verts = num_verts * sizeof(float) * VERTEX_ATTRUBUTES;
	size_inds = num_verts * sizeof(int);

	verts = malloc(size_verts);
	inds = malloc(size_inds);


	// Convert a list of verts to some indicies and verticies
	num_inds = 0;
	for (int i=0;i<num_verts;i++) {
		for (int k=0;k<VERTEX_ATTRUBUTES;k++) {
			vertex[k] = vertices[i+k]
		}
		
		int is_repeat = 0;
		for (int m=0;m<num_inds;m++) {
			for (int g=0;g<VERTEX_ATTRUBUTES;g++) {
				if (vertex[g] != verts[g + m*VERTEX_ATTRUBUTES]) {
					is_repeat = 1;
				}
			}
		}
		if (!is_repeat) {
			for (int h=0;h<VERTEX_ATTRUBUTES;h++) {
				verts[h + inds*VERTEX_ATTRUBUTES] = vertex[h];
			}
			num_inds++;
		}
		inds[i] = num_inds;
	}

	free(vertex);

	output_mesh = mesh_add_indexed_vertices(mesh, mode, verts, size_verts, inds, size_inds);

	return output_mesh;
}*/

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Mesh mesh_generate_rect(float width, float height) {
	Mesh mesh;
	float vertices[20] = {
		-width/2, height/2, 0.0f, 0.0f, 1.0f,
		width/2, height/2, 0.0f, 1.0f, 1.0f,
		width/2, -height/2, 0.0f, 1.0f, 0.0f,
		-width/2, -height/2, 0.0f, 0.0f, 0.0f};
	int indices[6] = {
		3, 0, 1,
		1, 2, 3};
	mesh = mesh_initialize();
	mesh = mesh_add_indexed_vertices(mesh, GL_STATIC_DRAW, vertices, sizeof(float) * 20, indices, sizeof(int) * 6);
	mesh_build();
	return mesh;
}
