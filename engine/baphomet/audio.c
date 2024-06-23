#include <baphomet/audio.h>

PaStreamParameters input_params, output_params;

void audio_initialize() {
	PaError err;
	fprintf(stderr, "\tInitializing PortAudio...\n");

	// Initialize portaudio
	err = Pa_Initialize();
	if (err != paNoError) {
		fprintf(stderr, "[E]\tIn audio_initialize(): %s\n",Pa_GetErrorText(err));
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
	output_params.sampleFormat = paFloat32;
	output_params.suggestedLatency = output_info->defaultLowOutputLatency; // Temporarily set to low!!!!
	output_params.hostApiSpecificStreamInfo = NULL;
	fprintf(stderr, "NOTE\tAbove errors may be caused by faulty alsa configuration and can be safely ignored\n");
	fprintf(stderr, "[*]\tPortAudio Initialized\n");
} // CONSIDER NOT SETTING ALL THE CHANNELS HERE FOR EVERYTHING EVAR

void audio_terminate() {
	Pa_Terminate();
}

int audio_get_default_input_device() {
	return Pa_GetDefaultInputDevice();
}

int audio_get_default_output_device() {
	return Pa_GetDefaultOutputDevice();
}

// Seg fault will be given on nonexistant device ADD ERROR CAPTURE
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
	Sound sound;
	PaError err;
	SNDFILE* soundfile;
	PaStreamParameters output_params;

	// Load file
	soundfile = sf_open(filepath, SFM_READ, &(sound.soundfile_info));
	if (soundfile == NULL) {
		fprintf(stderr, "An error occured when opening: %s\n", filepath);
	}

	// Set sound variables
	sound.user_data = (void*)soundfile;
	sound.rate = sound.soundfile_info.samplerate;
	output_params.device = Pa_GetDefaultOutputDevice();
	output_params.channelCount = sound.soundfile_info.channels;
	output_params.sampleFormat = paFloat32;
	output_params.suggestedLatency = Pa_GetDeviceInfo( output_params.device )->defaultLowOutputLatency;
	output_params.hostApiSpecificStreamInfo = NULL;

	// Open stream
	err = Pa_OpenStream(&(sound.stream), NULL, &output_params, sound.rate, DEFAULT_FRAME_LENGTH, paClipOff, SND_CALLBACK_SNDFILE, sound.user_data);
	if (err != paNoError) {
		fprintf(stderr, "audio_create_callback(): Unable to open stream -> %s\n", Pa_GetErrorText(err));
	}

	return sound;
}

void asset_unload_sound(Sound* sound) {
	PaError err;
/*
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
	}*/
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

static int _audio_callback_libsndfile( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData ) {
    float *out = (float*)outputBuffer;

		sf_readf_float((SNDFILE*)userData, out, framesPerBuffer);

    return paContinue;
}
