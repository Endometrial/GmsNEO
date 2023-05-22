#include <engine/asset.h>

Sprite asset_load_sprite(char* image_filepath, GLint texture_wrap, 
	GLint texture_filter) {
	Sprite sprite;
	unsigned int texture;
	Image picture;
	Mesh mesh;
	GLenum format;

	picture = image_load(image_filepath);

	format = (picture.color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, picture.width, picture.height, 0, format, GL_UNSIGNED_BYTE, picture.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter); // for scaling up

	// This is pretty so im leaving it even though its useless now. fuck off ;3 <3
	float ratio = (float)picture.height / (float)picture.width;
	mesh = (ratio>1.0f) ? mesh_generate_rect(1.0f/ratio, 1.0f) : mesh_generate_rect(1.0f, 1.0f*ratio);

	//mesh = mesh_generate_rect((float)picture.width, (float)picture.height);

	sprite.mesh = mesh;
	sprite.texture = texture;
	sprite.image = picture;

	return sprite;
}