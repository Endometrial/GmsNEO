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
#include <sndfile.h>

#include <decoder/ogg.h>

#define SND_CALLBACK_SNDFILE &_audio_callback_libsndfile

typedef struct {
	int					rate;
	void*				user_data;
	SF_INFO			soundfile_info;
	PaStreamCallback*	callback;
	PaStream*			stream;
} Sound;

void audio_initialize();
void audio_terminate();

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

static int _audio_callback_libsndfile( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData );

#endif
