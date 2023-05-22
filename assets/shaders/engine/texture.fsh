#version 330 core
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D textureColor;

void main() {
	fragColor = texture(textureColor, texCoord);
}
