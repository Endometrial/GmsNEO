#ifndef OGG_H
#define OGG_H

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	FILE* 				filepointer;
	ogg_stream_state 	stream_state;
	ogg_sync_state 		sync_state;
	ogg_packet 			packet;
	ogg_page 			page;
	vorbis_block 		block;
	vorbis_comment 		comments;
	vorbis_info 		info;
	vorbis_dsp_state 	state;
}	OggDecoder;

typedef struct {
	int length;
	int16_t* samples;
} Samplei16;

OggDecoder ogg_decoder_open(char* filepath);
void ogg_decoder_close(OggDecoder* decoder);
int ogg_decoder_get_pcm_i16(OggDecoder* decoder, Samplei16* sample);
int ogg_decoder_get_channels(OggDecoder* decoder);
int ogg_decoder_get_rate(OggDecoder* decoder);

void ogg_sample_initialize_i16(Samplei16* sample);

#endif