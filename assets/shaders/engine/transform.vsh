#version 330 core
layout(location = 0) in vec3 vertexCoord;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(vertexCoord, 1.0f);
	//gl_Position = vec4(vertexCoord, 1.0f);
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
