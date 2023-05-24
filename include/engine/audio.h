#ifndef AUDIO_H
#define AUDIO_H

#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ogg/ogg.h>

typedef struct {
	float left_phase;
	float right_phase;
} paTestData;

typedef struct {
	PaStreamCallback* callback;
	long seconds;
	pthread_t id;
} Sound;

Sound audio_play_callback_async(long secs);
PaStream* audio_open_stream(int num_inputs, int num_outputs, double sample_rate, PaStreamCallback callback);
void audio_close_stream(PaStream*);
void audio_play_stream(PaStream* stream);
void audio_stop_stream(PaStream* stream);
void audio_play_callback();
static int audio_callback_square(  const void *buffer_in, void *buffer_out, unsigned long buffer_frames, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flags, void* user_data);
void audio_initialize();
void audio_terminate();

#endif