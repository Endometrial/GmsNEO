#ifndef AUDIO_H
#define AUDIO_H

#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <engine/ogg.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>

#define SND_TYPE_UNKNOWN	0x0
#define SND_TYPE_VORBISFILE	0x1
#define SND_TYPE_SQUARE		0x2 // To be developed
#define SND_TYPE_CUSTOM		0xF // To be developed

#define FRAME_LENGTH 4096

#define SND_CALLBACK_VORBISFILE &_callback_oggvorbis_i16

typedef struct {
	int					type;
	int					rate;
	void*				user_data;
	PaStreamCallback*	callback;
	PaStream*			stream;
} Sound;

void audio_initialize();
void audio_terminate();
Sound audio_create_sound(int type, int rate, void* user_data); // Subject to change
PaStreamParameters audio_get_input_parameters();
PaStreamParameters audio_get_output_parameters();
void audio_set_input_device(int device_index);
void audio_set_output_device(int device_index);
char** audio_get_devices_list();
const PaDeviceInfo* audio_get_device_info(int device_index);
void audio_sound_play(Sound sound);
void audio_sound_pause(Sound sound);

static int _callback_oggvorbis_i16(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

#endif