#version 330 core
out vec4 fragColor;

// in type variable_name
// out type variable_name
// uniform type uniform_name

uniform vec4 fshColor;

void main() {
	fragColor = fshColor;
}
