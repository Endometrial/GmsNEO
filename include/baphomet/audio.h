#ifndef BAPHOMET_AUDIO_H
#define BAPHOMET_AUDIO_H

#include <portaudio.h>

#include <decoder/ogg.h>

#define SND_TYPE_UNKNOWN	0x0
#define SND_TYPE_VORBISFILE	0x1
#define SND_TYPE_SQUARE		0x2 // To be developed
#define SND_TYPE_SINE		0x3 // To be developed
#define SND_TYPE_SAW		0x4 // To be developed
#define SND_TYPE_SAW_INV	0x5 // To be developed
#define SND_TYPE_CUSTOM		0xF // To be developed

#define DEFAULT_FRAME_LENGTH 4096
#define DEFAULT_SAMPLE_RATE 44000

#define SND_CALLBACK_VORBISFILE &_audio_callback_oggvorbis_i16
#define SND_CALLBACK_SQUARE &_audio_callback_chip_i16
#define SND_CALLBACK_SINE SND_CALLBACK_SQUARE
#define SND_CALLBACK_SAW SND_CALLBACK_SQUARE
#define SND_CALLBACK_SAW_INV SND_CALLBACK_SQUARE

typedef struct {
	int					type;
	int					rate;
	void*				user_data;
	PaStreamCallback*	callback;
	PaStream*			stream;
} Sound;

typedef struct {
	int 				rate;
	int 				frequency;
	int 				type;
} SynthData;



void audio_initialize();
void audio_terminate();
Sound audio_create_chip(int type, long frequency);
Sound audio_create_from_decoder(int type, int rate, void* user_data);
Sound audio_create_from_custom_callback(PaStreamCallback* callback, int rate, int frames, PaStreamCallbackFlags flags, void* user_data);
Sound audio_open_stream(PaStreamCallback* callback, int type, int rate, int frames, PaStreamCallbackFlags flags, void* user_data);
PaStreamParameters audio_get_input_parameters();
PaStreamParameters audio_get_output_parameters();
void audio_set_input_device(int device_index);
void audio_set_output_device(int device_index);
char** audio_get_devices_list();
const PaDeviceInfo* audio_get_device_info(int device_index);
void audio_sound_play(Sound sound);
void audio_sound_pause(Sound sound);

static int _audio_callback_oggvorbis_i16(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
static int _audio_callback_chip_i16(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

#endif