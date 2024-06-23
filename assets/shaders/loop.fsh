#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 

/*
#version 330 core
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D textureColor;

uniform float loop_offset;

void main() {
	fragColor = texture(textureColor, vec2(texCoord.x+loop_offset, texCoord.y));
}
*/
