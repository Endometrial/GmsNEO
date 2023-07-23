#include <baphomet/audio.h>

PaStreamParameters input_params, output_params;

void audio_initialize() {
	PaError err;

	// Initialize portaudio
	err = Pa_Initialize();
	if (err != paNoError) {
		fprintf(stderr, "audio_initialize(): %s\n",Pa_GetErrorText(err));
	}

	// Set default stream parameters
	input_params.device = Pa_GetDefaultInputDevice();
	const PaDeviceInfo* input_info = Pa_GetDeviceInfo(input_params.device);
	input_params.channelCount = input_info->maxInputChannels;
	input_params.sampleFormat = paFloat32;
	input_params.suggestedLatency = input_info->defaultHighInputLatency;
	input_params.hostApiSpecificStreamInfo = NULL;

	output_params.device = Pa_GetDefaultOutputDevice();
	const PaDeviceInfo* output_info = Pa_GetDeviceInfo(output_params.device);
	output_params.channelCount = output_info->maxOutputChannels;
	output_params.sampleFormat = paInt16;
	output_params.suggestedLatency = output_info->defaultHighOutputLatency;
	output_params.hostApiSpecificStreamInfo = NULL;}

void audio_terminate() {
	Pa_Terminate();
}

Sound audio_create_from_custom_callback(PaStreamCallback* callback, int rate, int frames, PaStreamCallbackFlags flags, void* user_data) {
	return audio_open_stream(callback, SND_TYPE_CUSTOM, rate, frames, flags, user_data);
}

Sound audio_create_from_decoder(int type, int rate, void* user_data) {
	PaStreamCallback* callback;
	switch(type) {
		case SND_TYPE_VORBISFILE:
			callback = SND_CALLBACK_VORBISFILE;
			break;
		default:
			fprintf(stderr, "audio_create_sound(): Type not found!\n");
			exit(-1);
			break;
	}

	return audio_open_stream(callback, type, rate, DEFAULT_FRAME_LENGTH, paNoFlag, user_data);
}

Sound audio_open_stream(PaStreamCallback* callback, int type, int rate, int frames, PaStreamCallbackFlags flags, void* user_data) {
	Sound sound;
	PaError err;
	sound.user_data = user_data;
	sound.rate = rate;
	sound.type = type;
	err = Pa_OpenStream(&sound.stream, &input_params, &output_params, sound.rate, frames, flags, callback, sound.user_data);
	if (err != paNoError) {
		fprintf(stderr, "audio_create_callback(): Unable to open stream -> %s\n", Pa_GetErrorText(err));
	}
	return sound;
}

int audio_get_default_input_device() {
	return Pa_GetDefaultInputDevice();
}

int audio_get_default_output_device() {
	return Pa_GetDefaultOutputDevice();
}

// Seg fault will be given on nonexistant device
void audio_set_input_device(int device_index) {
	const PaDeviceInfo* device_info = Pa_GetDeviceInfo(device_index);
	input_params.suggestedLatency = device_info->defaultHighInputLatency;
	input_params.channelCount = device_info->maxInputChannels;
	input_params.device = device_index;
}

// Seg fault will be given on nonexistant device
void audio_set_output_device(int device_index) {
	const PaDeviceInfo* device_info = Pa_GetDeviceInfo(device_index);
	output_params.suggestedLatency = device_info->defaultHighOutputLatency;
	output_params.channelCount = device_info->maxOutputChannels;
	output_params.device = device_index;
}

char** audio_get_devices_list() {
	char** device_list;
	int devices = Pa_GetDeviceCount();
	for (int i=0; i<devices; i++) {
		const PaDeviceInfo* device_info;
		device_info = Pa_GetDeviceInfo(i);
		device_list[i] = (char*)device_info->name;
	}
	return device_list;
}

const PaDeviceInfo* audio_get_device_info(int device_index) {
	return Pa_GetDeviceInfo(device_index);
}

PaStreamParameters audio_get_input_parameters() {
	return input_params;}

PaStreamParameters audio_get_output_parameters() {
	return output_params;}

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

	return sound;
}

void asset_unload_sound(Sound* sound) {
	PaError err;

	err = Pa_CloseStream(sound->stream);
	if (err != paNoError) {
		fprintf(stderr, "asset_unload_sound(): Unable to close stream -> %s\n", Pa_GetErrorText(err));
		exit(-1);
	}

	switch(sound->type) {
		case SND_TYPE_VORBISFILE:
			ogg_decoder_close(sound->user_data);
			break;
		default:
			fprintf(stderr, "asset_unload_sound(): sound type does not exist!\n");
			break;
	}
}

void audio_sound_play(Sound sound, int loop) {
	PaError err;
	err = Pa_StartStream(sound.stream);
	(err != paNoError) ? fprintf(stderr, "audio_sound_play(): %s\n", Pa_GetErrorText(err)) : 1;
}

void audio_sound_pause(Sound sound) {
	PaError err;
	err = Pa_StopStream(sound.stream);
	(err != paNoError) ? fprintf(stderr, "audio_sound_pause(): %s\n", Pa_GetErrorText(err)) : 1;
}

static int _audio_callback_oggvorbis_i16(const void *input_buffer, void *output_buffer, unsigned long buffer_frames, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags flags, void* user_data) {
	OggDecoder* decoder = (OggDecoder*)user_data;
	int16_t* out = (int16_t*)output_buffer;
	
	// Read pcm into the buffer :3
	(ogg_decoder_get_pcm_i16(decoder, &out, buffer_frames)) ? ogg_decoder_rewind(decoder) : 1;
	return 0;
}