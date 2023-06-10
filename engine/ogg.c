#include <engine/ogg.h>

OggDecoder* ogg_decoder_open(char* filepath) {
	OggDecoder* decoder;
	char* audio_buffer;
	int bytes_read;

	// Allocate data for the decoder
	decoder = malloc(sizeof(OggDecoder));

	// Load the file
	decoder->filepointer = fopen(filepath, "rb");
	if (!decoder->filepointer) {
		fprintf(stderr,"Ogg/Vorbis Decoder: cannot open %s ;-;\n", filepath);
		exit(-1);
	}

	// Initialize libogg & read in some bytes
	ogg_sync_init(&decoder->sync_state);
	audio_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
	bytes_read = fread(audio_buffer, sizeof(char), 4096, decoder->filepointer);
	(bytes_read < 4096) ? fprintf(stderr, "Ogg/Vorbis Decoder: EOF!\n") : 1;

	// Submit data and get the first page
	ogg_sync_wrote(&decoder->sync_state, bytes_read);
	if (ogg_sync_pageout(&decoder->sync_state, &decoder->page) != 1) {
		fprintf(stderr, "Ogg/Vorbis Decoder: Bitstream not found! :(\n");
		exit(-1);
	}

	// Initialize stream and data types
	ogg_stream_init(&decoder->stream_state, ogg_page_serialno(&decoder->page));
	vorbis_info_init(&decoder->info);
	vorbis_comment_init(&decoder->comments);

	// Read and interpret first header packet
	ogg_stream_pagein(&decoder->stream_state, &decoder->page);
	ogg_stream_packetout(&decoder->stream_state, &decoder->packet);
	if (vorbis_synthesis_headerin(&decoder->info, &decoder->comments, &decoder->packet) < 0) {
		fprintf(stderr, "Ogg/Vorbis Decoder: %s not vorbis! >:3\n", filepath);
		exit(-1);
	}

	// Get Comment and Codebook headers
	int headers = 0;
	while (headers<2) {
		// Get a page out :3
		if (ogg_sync_pageout(&decoder->sync_state, &decoder->page) == 1) {
			ogg_stream_pagein(&decoder->stream_state, &decoder->page);
			ogg_stream_packetout(&decoder->stream_state, &decoder->packet);
			if (vorbis_synthesis_headerin(&decoder->info, &decoder->comments, &decoder->packet)) {
				fprintf(stderr, "Ogg/Vorbis Decoder: Error in header #%i \n",headers);
			}
			headers++;
		}
		// Read data in :3
		audio_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
		bytes_read = fread(audio_buffer, sizeof(char), 4096, decoder->filepointer);	
		(bytes_read < 4096) ? fprintf(stderr, "Ogg/Vorbis Decoder: EOF!\n") : 1;
		ogg_sync_wrote(&decoder->sync_state, bytes_read);
	}

	// Initialize vorbis data types
	vorbis_synthesis_init(&decoder->state, &decoder->info);
	vorbis_block_init(&decoder->state, &decoder->block);

	return decoder;}

// Loads int16_ts into buffer and returns 0 (done) 1 (more data can be gathered)
int ogg_decoder_get_pcm_i16(OggDecoder* decoder, Samplei16* sample) {
	int channels, samples, bytes_read, len, sample_data;
	char* load_buffer = (char*)0;
	float** raw_pcm = (float**)0;

	// Set the bits and other small variables
	short bits = 16;
	int eos = 0;

	// Initialize some variables
	channels = (int)decoder->info.channels;
	sample_data = (float)pow(2, bits) / 2.0f;

	while (((samples=vorbis_synthesis_pcmout(&decoder->state, &raw_pcm)) == 0)) {
		while(ogg_stream_packetout(&decoder->stream_state, &decoder->packet) != 1) {
			if (ogg_sync_pageout(&decoder->sync_state, &decoder->page) == 1) {
				ogg_stream_pagein(&decoder->stream_state, &decoder->page);
				if (ogg_page_eos(&decoder->page)) {
				eos = 1;
				}
			} else {
				load_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
				bytes_read = fread(load_buffer, sizeof(char), 4096, decoder->filepointer);
				(bytes_read < 4096) ? fprintf(stderr,"EOF!, EOS imminent\n") : 1;
				ogg_sync_wrote(&decoder->sync_state, bytes_read);
			}
		}
		vorbis_synthesis(&decoder->block, &decoder->packet);
		vorbis_synthesis_blockin(&decoder->state, &decoder->block);
	}

	// Allocate the buffer (or reallocate if it already exists)
	sample->samples = realloc(sample->samples, channels * samples * sizeof(int16_t));
	sample->length = samples;

	// Read samples into the buffer
	for (int i=0; i<channels; i++) {
		int16_t* ptr = sample->samples + i;
		float* mono = raw_pcm[i];
		for (int m=0; m<samples; m++) {
			int16_t val = floor(mono[m]*((float)sample_data/2.0f) + 0.5f);

      	    val = (val > sample_data/2) ? sample_data/2 : val;
      	    val = (val < -sample_data/2) ? -sample_data/2 : val;

     	    *ptr=val;
     	    ptr+=channels;
   
		}
	}

	// Tell vorbis how many samples were read & return ^w^
	vorbis_synthesis_read(&decoder->state, samples);
	return eos;}

void ogg_decoder_close(OggDecoder* decoder) {
	vorbis_block_clear(&decoder->block);
	vorbis_dsp_clear(&decoder->state);
	ogg_stream_clear(&decoder->stream_state);
	vorbis_comment_clear(&decoder->comments);
	vorbis_info_clear(&decoder->info);
	ogg_sync_clear(&decoder->sync_state);
	fclose(decoder->filepointer);
	free(decoder);}

int ogg_decoder_get_channels(OggDecoder* decoder) {
	return decoder->info.channels;}

int ogg_decoder_get_rate(OggDecoder* decoder) {
	return decoder->info.rate;}

void ogg_sample_initialize_i16(Samplei16* sample) {
	sample->samples = malloc(0);
	sample->length = 0;}
