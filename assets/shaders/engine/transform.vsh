#version 330 core
layout(location = 0) in vec3 vertexCoord;
layout(location = 1) in vec2 aTexCoord;
out vec2 texCoord;
uniform mat4 local_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
	gl_Position = projection_matrix * view_matrix * local_matrix * vec4(vertexCoord, 1.0f);
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
