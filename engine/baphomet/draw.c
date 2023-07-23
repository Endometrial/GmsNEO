#include <baphomet/draw.h>

Shader active_shader;

void draw_initialize() {
	if (!glfwInit()) {
		printf("draw_initialize(): Failed to initialize glfw :(");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void draw_terminate() {
	glfwTerminate();
}

void draw_clear(float r, float g, float b, float a) {
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Transform generation will be given too math.h when she is ready ex math_generate_transform_euler
void draw_mesh_ext(Mesh mesh, float x, float y, float z, float x_scale, float y_scale, float z_scale, float x_rot, float y_rot, float z_rot) {
	int cx = cos(x_rot);
	int sx = sin(x_rot);
	int cy = cos(y_rot);
	int sy = sin(y_rot);
	int cz = cos(z_rot);
	int sz = sin(z_rot);
	mat4 local_matrix = {
	{ x_scale*(cy+cz),	   		   	sz,			    -sy,			0.0f },
	{ 			  -sz, y_scale*(cx+cz),	   		     sx,			0.0f },
	{ 			   sy, 	 		   -sx, z_scale*(cx+cy),	 		0.0f },
	{    		    x,    		     y,    		      z,    		1.0f }};
	Shader shader;
	shader = draw_get_shader();

	shader_set_uniform_mat4(shader, "local_matrix", local_matrix);
	shader_set_uniform_mat4(shader, "projection_matrix", *camera_get_projection_matrix());
	shader_set_uniform_mat4(shader, "view_matrix", *camera_get_view_matrix());

	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.elements, GL_UNSIGNED_INT, 0);
}

void draw_mesh_2d(Mesh mesh, float x, float y, float scale, float rot, float depth) {
	draw_mesh_ext(mesh, x, y, depth, scale, scale, scale, 0.0f, 0.0f, rot);
}

void draw_set_texture(Texture texture) {
	glBindTexture(GL_TEXTURE_2D, texture.texture);
}

void draw_set_texture_ext(Texture texture, GLint tex_wrap, GLint tex_filter) {
	glBindTexture(GL_TEXTURE_2D, texture.texture);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex_filter); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex_filter); // for scaling up
}

void draw_set_shader(Shader shader) {
	active_shader = shader;
	glUseProgram(active_shader.program);
}

void draw_set_mode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void draw_set_blendmode(GLenum sfactor, GLenum dfactor) {
	glBlendFunc(sfactor, dfactor);
	glEnable(GL_BLEND);
}

Shader draw_get_shader() {
	return active_shader;
}