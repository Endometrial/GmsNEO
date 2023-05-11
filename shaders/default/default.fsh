#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D textureColor;

void main() {
	fragColor = texture(textureColor, texCoord);
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
