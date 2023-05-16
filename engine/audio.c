#include <engine/audio.h>

Sound audio_play_callback_async(long secs) {
	Sound* sound;
	// Struct must be allocated on heap
	sound = malloc(sizeof(*sound));
	sound->seconds = secs;
	sound->callback = &audio_callback_square;
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, audio_play_callback, sound);
	sound->id = thread_id;
	return *sound;
}

void audio_play_callback(Sound* sound) {
	PaStream* stream;
	stream = audio_open_stream(0,2,44100,sound->callback);
	audio_play_stream(stream);
	Pa_Sleep(1000 * sound->seconds);
	audio_stop_stream(stream);
	audio_close_stream(stream);
}

PaStream* audio_open_stream(int num_inputs, int num_outputs, double sample_rate, PaStreamCallback* callback) {
	PaStream* stream;
	PaError err;
	paTestData data;

	err = Pa_OpenDefaultStream(&stream, num_inputs, num_outputs, paFloat32, sample_rate, 256, callback, &data);
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
	}

	return stream;
}

void audio_close_stream(PaStream* stream) {
	PaError err;
	err = Pa_CloseStream(stream);
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
	}
}

void audio_play_stream(PaStream* stream) {
	PaError err;
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
	}
}

void audio_stop_stream(PaStream* stream) {
	PaError err;
	err = Pa_StopStream(stream);
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
	}
}


static int audio_callback_square(  const void *buffer_in, 
							void *buffer_out, 
							unsigned long buffer_frames, 
							const PaStreamCallbackTimeInfo* time_info, 
							PaStreamCallbackFlags status_flags, 
							void* user_data) {

	paTestData *data = (paTestData*)user_data;
	float* out = (float*)buffer_out;

	for (unsigned int i=0; i<buffer_frames; i++) {
		*(out++) = data->left_phase;
		*(out++) = data->right_phase;
		data->left_phase += 0.f;
		if (data->left_phase >= 1.0f) data->left_phase -=2.0f;
		data->right_phase += 0.3f;
		if (data->right_phase >= 1.0f) data->right_phase -=2.0f;
	}
	return 0;
}

void audio_initialize() {
	PaError err = Pa_Initialize();
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	}
}

void audio_terminate() {
	PaError err = Pa_Terminate();
	if (err != paNoError) {
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	}
}