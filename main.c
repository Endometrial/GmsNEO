#include "main.h"

// Bulky no EBO method
float vertices2[] = {
	// tri one
	0.5f, 0.5f, 0.0f,
	0.5f, -.5f, 0.0f,
	-.5f, 0.5f, 0.0f,
	// tri two
	0.5f, -.5f, 0.0f,
	-.5f, -.5f, 0.0f,
	-.5f, 0.5f, 0.0f
};

float vertices[] = {
	0.5f, 0.5f, 0.0f,	// top right
	0.5f, -.5f, 0.0f,	// bottom right
	-.5f, -.5f, 0.0f,	// bottom left
	-.5f, 0.5f, 0.0f	// top left
};

unsigned int indices[] = {
	0, 1, 3,// tri one
	1, 2, 3	// tri two
};

char* vshFilepath = "shaders/default/default.vsh";
char* fshFilepath = "shaders/default/default.fsh";


int main() {
	unsigned int fragmentShader, vertexShader, shaderProgram;
	GLFWwindow* window;
	Mesh mesh, mesh2;

	window = window_initialize(800,600,"Tile");
	vertexShader = shader_build(vshFilepath, GL_VERTEX_SHADER);
	fragmentShader = shader_build(fshFilepath, GL_FRAGMENT_SHADER);
	shaderProgram = shader_program_create(vertexShader, fragmentShader);

	mesh = mesh_initialize();
	//mesh = mesh_add_vertices(mesh ,GL_STATIC_DRAW, vertices, sizeof(vertices), indices, sizeof(vertices));
	mesh = mesh_add_vertices(mesh ,GL_STATIC_DRAW, vertices2, sizeof(vertices2));
	mesh_build();

	//mesh2 = mesh_initialize();
	//mesh2 = mesh_add_vertices(mesh, GL_STATIC_DRAW, vertices2, sizeof(vertices2));
	//mesh_build();

	glViewport(0,0,800,600);

	//int width, height, channels;
	//unsigned char* data = stbi_load();

	while (!glfwWindowShouldClose(window)) {
	
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		}

		draw_clear(0.2f, 0.3f, 0.8f, 1.0f);
		draw_set_mode(GL_FILL);

		float time = glfwGetTime();
		float green = (sin(time) / 2.0f) + 0.5f;

		shader_program_apply(shaderProgram);
		shader_set_uniform_vec4(shaderProgram, "fshColor", 0.0f, green, 0.0f, 1.0f);



		draw_mesh(mesh);
		
		// glBindVertexArray(0) Reset the array

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

GLFWwindow* window_initialize(int width, int height, const char* title) {
	GLFWwindow* window;

	if (!glfwInit()) {
		endp("Failed to initialize glfw :(");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		endp("Failed to create window :(");
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// TODO: what in the goddamn fuck is this notation
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		endp("Failed to initialize glad :(");
	}

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void endp(char* err) {
	printf("%s\n",err);
	glfwTerminate();
	exit(0);
}
