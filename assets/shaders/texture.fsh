#version 330 core
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D textureColor;

uniform vec2 tex_offset;
uniform vec2 tex_scale;

uniform vec4 tri_color;

void main() {

	fragColor = texture(textureColor, (texCoord+tex_offset)*tex_scale)*vec4(tri_color.r, tri_color.g, tri_color.b, 1.0f);
}
