#include <baphomet/asset.h>

Texture asset_load_texture(char* filepath, GLint texture_wrap, 
	GLint texture_filter) {
	int format, height, width;
	unsigned char* data;
	Texture texture;

	// Check the file type
	//sprite.type = (png_decoder_is_png(filepath)) ? IMG_TYPE_PNG : IMG_TYPE_UNKNOWN;
	texture.type = IMG_TYPE_PNG;

	// Generate a texture
	glGenTextures(1, &texture.texture);
	glBindTexture(GL_TEXTURE_2D, texture.texture);

	// Switch over the filetype to extract data
	switch(texture.type) {
		case IMG_TYPE_PNG:
			PngDecoder* decoder = png_decoder_open(filepath);
			texture.user_data = decoder;
			data = png_decoder_get_data(decoder);
			width = png_decoder_get_width(decoder);
			height = png_decoder_get_height(decoder);
			format = (png_decoder_get_color_type(decoder) & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			png_decoder_free_data(data); // Free the data as it is no longer needed
			break;
		default:
			// Report that no filetype could be matched & exit
			fprintf(stderr, "asset_load_sprite(): file provided was not of a supported type!\n");
			fprintf(stderr, "	supported types include : ");
			for (int i=0; supported_image_filetypes[i] != NULL; i++) {
				fprintf(stderr, "%s ", supported_image_filetypes[i]);}
			fprintf(stderr, "\n");
			exit(-1);
			break;
	}

	// Set variables (will be made obsolete in the future (ex sprite.c))
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter); // for scaling down
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter); // for scaling up

	// This is pretty so im leaving it even though its useless now. fuck off ;3 <3
	//float ratio = (float)height / (float)width;
	//sprite.mesh = (ratio>1.0f) ? mesh_generate_rect(1.0f/ratio, 1.0f) : mesh_generate_rect(1.0f, 1.0f*ratio);
	//sprite.mesh = mesh_generate_rect(0.0f,0.0f,(float)width, (float)height, 0.0f);

	// Free data plz ;w;
	return texture;}

void asset_unload_texture(Texture* texture) {

	// Delete textures
	glDeleteTextures(1, &texture->texture);
	
	// Delete the mesh

	// Delete whatever is contained within user data
	switch(texture->type) {
		case IMG_TYPE_PNG:
			png_decoder_close(texture->user_data);
			break;
		default:
			fprintf(stderr, "asset_unload_sprite(): Unknown filetype!\n");
			break;
	}}

Sound asset_load_sound(char* filepath) {
	PaStreamParameters in, out;
	int filetype;
	Sound sound;
	PaError err;

	// Check the filetype
	filetype = (ogg_decoder_is_vorbis(filepath)) ? SND_TYPE_VORBISFILE : SND_TYPE_UNKNOWN;

	// Switch over the possible filetypes & populate struct
	switch(filetype) {
		case SND_TYPE_VORBISFILE:
			OggDecoder* decoder = ogg_decoder_open(filepath);
			sound = audio_create_from_decoder(filetype, ogg_decoder_get_rate(decoder), (void*)decoder);
			break;
		default:
			// Report that no filetype could be matched & exit
			fprintf(stderr, "asset_load_sound(): file provided was not of a supported type!\n");
			fprintf(stderr, "	supported types include : ");
			for (int i=0; supported_audio_filetypes[i] != NULL; i++) {
				fprintf(stderr, "%s ", supported_audio_filetypes[i]);}
			fprintf(stderr, "\n");
			exit(-1);
	}

	return sound;}

void asset_unload_sound(Sound* sound) {
	PaError err;

	switch(sound->type) {
		case SND_TYPE_VORBISFILE:
			ogg_decoder_close(sound->user_data);
		default:
			fprintf(stderr, "asset_unload_sound(): sound type does not exist!\n");
			break;
	}

	err = Pa_CloseStream(sound->stream);
	if (err != paNoError) {
		fprintf(stderr, "asset_unload_sound(): Unable to close stream -> %s\n", Pa_GetErrorText(err));
		exit(-1);
	}}

Room asset_load_room(char* filepath) {
	Room room;
	XmlDecoder* decoder; // There is only one kind of room
	xmlNode* current_node;

	// Allocate space for the room instance list
	room.instance_list = malloc(0);
	room.num_instances = 0;

	// Load the xml
	decoder = xml_decoder_open(filepath);

	// Loading <background> <instance>
	current_node = xml_node_get_children(xml_decoder_get_root_node(decoder));
	while (current_node != NULL) {
		if (xml_node_is_element_node(current_node)) {
			switch(xml_node_get_name(current_node)[0]) {
				case 'b': // <background>
					fprintf(stderr, "asset_load_room(): Backgrounds are not yet supported\n");
					break;
				case 'i': // <instance>
					xmlNode* instance_node = xml_node_get_children(current_node);
					for (1; instance_node!=NULL; instance_node=instance_node->next) {
						if (xml_node_is_element_node(instance_node)) {
							switch(xml_node_get_name(instance_node)[0]) {
								case 'o':
									// Reallocate & update room data
									room.num_instances++;
									room.instance_list = realloc(room.instance_list, room.num_instances*sizeof(Object));

									// Load an object
									room.instance_list[room.num_instances-1] = asset_load_object(xml_node_get_content(instance_node));
									break;
								case 'l':
									fprintf(stderr, "asset_load_room(): Object Locations are not yet supported\n");
									break;
								case 's':
									fprintf(stderr, "asset_load_room(): Scripts are not yet supported\n");
									break;
								default:
									fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(instance_node));
									break;
							}
						}
					}

					break;
				default:
					fprintf(stderr, "asset_load_room(): XML contains illegal node [%s]\n", xml_node_get_name(current_node));
					break;
			}
		}
		current_node = current_node->next; // Advance the node
	}

	// Free data and return the room :)
	xml_decoder_close(decoder);
	return room;}

void asset_unload_room(Room* room) {
	free(room->instance_list);}

Object asset_load_object(char* filepath) {
	Object object;

	object.handle = dlopen(filepath, RTLD_NOW);
	(object.handle == NULL) ? fprintf(stderr, "asset_load_object(): %s\n", dlerror()) : 1;

	object.create = dlsym(object.handle, "create");
	object.step = dlsym(object.handle, "step");
	object.draw = dlsym(object.handle, "draw");
	object.destroy = dlsym(object.handle, "destroy");
	object.cleanup = dlsym(object.handle, "cleanup");

	return object;
}

void asset_unload_object(Object* object) {
	object->cleanup();
	object->destroy();
	(dlclose(object->handle)) ? fprintf(stderr, "asset_unload_object(): %s\n", dlerror()) : 1;
}
