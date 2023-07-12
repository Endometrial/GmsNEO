#version 330 core
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D textureColor;

uniform float loop_offset;

void main() {
	fragColor = texture(textureColor, vec2(texCoord.x+loop_offset, texCoord.y));
}
