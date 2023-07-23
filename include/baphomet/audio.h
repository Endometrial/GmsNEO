#ifndef BAPHOMET_AUDIO_H
#define BAPHOMET_AUDIO_H

/*
	Audio.h
	Created: xxxx-xx-xx
	Description:
		Audio.h is intened to house scripts which:
			* Load/unload portaudio systems
			* Wrap portaudio functionality
			* Allow the playing of sounds & audio
*/


#include <portaudio.h>

#include <decoder/ogg.h>

#define SND_TYPE_UNKNOWN	0x0
#define SND_TYPE_VORBISFILE	0x1
#define SND_TYPE_CUSTOM		0xFF

#define DEFAULT_FRAME_LENGTH 4096
#define DEFAULT_SAMPLE_RATE 44000

#define SND_CALLBACK_VORBISFILE &_audio_callback_oggvorbis_i16

static char* supported_audio_filetypes[] = {"ogg(vorbis)\0", NULL};

typedef struct {
	int					type;
	int					rate;
	void*				user_data;
	PaStreamCallback*	callback;
	PaStream*			stream;
} Sound;

void audio_initialize();
void audio_terminate();
Sound audio_create_from_decoder(int type, int rate, void* user_data);
Sound audio_create_from_custom_callback(PaStreamCallback* callback, int rate, int frames, PaStreamCallbackFlags flags, void* user_data);
Sound audio_open_stream(PaStreamCallback* callback, int type, int rate, int frames, PaStreamCallbackFlags flags, void* user_data);
PaStreamParameters audio_get_input_parameters();
PaStreamParameters audio_get_output_parameters();
void audio_set_input_device(int device_index);
void audio_set_output_device(int device_index);
int audio_get_default_input_device();
int audio_get_default_output_device();
char** audio_get_devices_list();
const PaDeviceInfo* audio_get_device_info(int device_index);

Sound asset_load_sound(char* filepath);
void asset_unload_sound(Sound* sound);
void audio_sound_play(Sound sound, int loop);
void audio_sound_pause(Sound sound);

static int _audio_callback_oggvorbis_i16(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

#endif