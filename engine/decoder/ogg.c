#include <decoder/ogg.h>

OggDecoder* ogg_decoder_open(char* filepath) {
	OggDecoder* decoder;
	char* audio_buffer;
	int bytes_read;

	// Allocate some space for the decoder
	decoder = malloc(sizeof(OggDecoder));

	// Load the file
	decoder->filepointer = fopen(filepath, "rb");
	if (!decoder->filepointer) {
		fprintf(stderr,"ogg_decoder_open(): cannot open %s ;-;", filepath);
		exit(-1);
	}

	// Initialize libogg & read in some bytes
	ogg_sync_init(&decoder->sync_state);
	audio_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
	bytes_read = fread(audio_buffer, sizeof(char), 4096, decoder->filepointer);
	(bytes_read < 4096) ? fprintf(stderr, "ogg_decoder_open(): EOF!") : 1;

	// Submit data and get the first page
	ogg_sync_wrote(&decoder->sync_state, bytes_read);
	if (ogg_sync_pageout(&decoder->sync_state, &decoder->page) != 1) {
		fprintf(stderr, "ogg_decoder_open(): Bitstream not found! :(");
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
		fprintf(stderr, "ogg_decoder_open(): %s not vorbis! >:3", filepath);
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
				fprintf(stderr, "ogg_decoder_open(): Error in header #%i ",headers);
			}
			headers++;
		}
		// Read data in :3
		audio_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
		bytes_read = fread(audio_buffer, sizeof(char), 4096, decoder->filepointer);
		(bytes_read < 4096) ? fprintf(stderr, "ogg_decoder_open(): EOF!") : 1;
		ogg_sync_wrote(&decoder->sync_state, bytes_read);
	}

	// Initialize vorbis data types
	vorbis_synthesis_init(&decoder->state, &decoder->info);
	vorbis_block_init(&decoder->state, &decoder->block);

	// Clear remainder & allocate some data for the remainder buffer
	decoder->remainder.buffer = malloc(0);
	decoder->remainder.frames = 0;

	// Set eos
	decoder->eos = 0;

	return decoder;}

int ogg_decoder_get_pcm_i16(OggDecoder* decoder, int16_t** buffer, int frames) {
	int channels, samples, bytes_read, len, sample_data, frames_read;
	char* load_buffer = (char*)0;
	float** raw_pcm;

	// Error if not enough data is provided
	// yes i know i could make it work anyway but like.... why....
	if (frames < MAX_OGG_SAMPLE_FRAMES) {
		fprintf(stderr, "ogg_decoder_get_pcm_i16(): frames must be greater than %i\n", MAX_OGG_SAMPLE_FRAMES);
	}

	// Set the bits and other small variables
	short bits = sizeof(int16_t) * 8;
	frames_read = 0;
	int page_eos = 0;

	// Initialize some variables
	channels = (int)decoder->info.channels;
	sample_data = (float)pow(2, bits) / 2.0f;

	// Reallocate the remainder as needed (aka everytime)
	decoder->remainder.buffer = realloc(decoder->remainder.buffer, MAX_OGG_SAMPLE_FRAMES * sizeof(int16_t) * channels);

	// Read in remainder (if it exists)
	if (decoder->remainder.frames > 0) {
		int16_t* bptr = (*buffer);						// Buffer
		int16_t* rptr = decoder->remainder.buffer;		// Remainder :3
		for (int i=0; i<(decoder->remainder.frames * channels); i++) {
			bptr[i] = rptr[i];
		}
		frames_read += decoder->remainder.frames;
	}

	// Loop until either there are no more samples or we have read all we need
	samples = !(0); // So it doesnt eval as false on first pass
	while ((frames_read < frames) && samples) {
		// Get next packet of pcm from executor vorbis unless another packet doesnt exist and the page is eos
		while (((samples=vorbis_synthesis_pcmout(&decoder->state, &raw_pcm)) == 0)) {
			if (page_eos == 1) {
				break; // If page is already eos then we know we are at eos
			}
			while((ogg_stream_packetout(&decoder->stream_state, &decoder->packet) == 0)) {
				if (ogg_sync_pageout(&decoder->sync_state, &decoder->page) == 1) {
					ogg_stream_pagein(&decoder->stream_state, &decoder->page);
				} else {
					load_buffer = ogg_sync_buffer(&decoder->sync_state, 4096l);
					bytes_read = fread(load_buffer, sizeof(char), 4096, decoder->filepointer);
					// (bytes_read < 4096) ? fprintf(stderr,"ogg_decoder_get_pcm_i16(): EOF!, EOS imminent\n") : 1;
					ogg_sync_wrote(&decoder->sync_state, bytes_read);
				}
				page_eos = (ogg_page_eos(&decoder->page)) ? 1 : 0; // Set page is eos based on if its eos
			}
			vorbis_synthesis(&decoder->block, &decoder->packet);
			vorbis_synthesis_blockin(&decoder->state, &decoder->block);
		}

		// Tell executor vorbis how many samples were read ^w^
		vorbis_synthesis_read(&decoder->state, samples);

		// Set available samples and remainder frames
		int available_samples = samples;
		decoder->remainder.frames = 0l;
		if ((frames_read + samples) >= frames) {
			available_samples = (frames-frames_read);
			decoder->remainder.frames = (long)(samples-available_samples);
		}

		// Read samples into the buffer
		for (int i=0; i<channels; i++) {
			int16_t* ptr = (*buffer) + i + frames_read*channels;
			float* mono = raw_pcm[i];
			for (int m=0; m<available_samples; m++) {
				int16_t val = floor(mono[m]*((float)sample_data/2.0f) + 0.5f);
      		    //val = (val > sample_data/2) ? sample_data/2 : val; // Guard against
      		    //val = (val < -sample_data/2) ? -sample_data/2 : val; // clipping
     		    *ptr=val;
     		    ptr+=channels;
			}
		}

		// Incriment frames_read by the ammount of samples
		frames_read+=available_samples;
	}

	// Read in the remainder
	if (decoder->remainder.frames > 0) {
		int offset = samples - decoder->remainder.frames;
		for (int i=0; i<channels; i++) {
			float* mono = raw_pcm[i];
			int16_t* rptr = decoder->remainder.buffer + i;
			for (int g=0; g<decoder->remainder.frames; g++) {
				int16_t val = floor(mono[g+offset]*((float)sample_data/2.0f) + 0.5f);
				//val = (val > sample_data/2) ? sample_data/2 : val; // Guard against
	   	   		//val = (val < -sample_data/2) ? -sample_data/2 : val; // clipping
	   	   		rptr[g<<1]=val;
			}
		}
	}

	// If data remains unread in finish out the packet and return eos
	decoder->eos = 0;
	if ((frames-frames_read) > 0) {
		for (int i=0; i<channels; i++) {
			int16_t* end_ptr = (*buffer) + (channels*frames_read);
			for (int m=0; m<(frames-frames_read); m++) {
				*end_ptr = 0;
				end_ptr+=channels;
			}
		}
		decoder->eos = 1;
		return 1; // EOS
	}
	return 0; // Not EOS
}

int ogg_decoder_eos(OggDecoder* decoder) {
	return decoder->eos;}

int ogg_decoder_get_channels(OggDecoder* decoder) {
	return decoder->info.channels;}

int ogg_decoder_get_rate(OggDecoder* decoder) {
	return decoder->info.rate;}

void ogg_decoder_close(OggDecoder* decoder) {
	vorbis_block_clear(&decoder->block);
	vorbis_dsp_clear(&decoder->state);
	ogg_stream_clear(&decoder->stream_state);
	vorbis_comment_clear(&decoder->comments);
	vorbis_info_clear(&decoder->info);
	ogg_sync_clear(&decoder->sync_state);
	fclose(decoder->filepointer);
	free(decoder->remainder.buffer);
	free(decoder);}

void ogg_decoder_rewind(OggDecoder* decoder) {
	fseek(decoder->filepointer, 0L, SEEK_SET);
}

int ogg_decoder_is_vorbis(char* filepath) {
	OggDecoder decoder;
	char* audio_buffer;
	int bytes_read;
	int is_vorbis = 1;

	// Open the file
	decoder.filepointer = fopen(filepath, "rb");
	if (!decoder.filepointer) {
		fprintf(stderr,"ogg_decoder_is_vorbis(): cannot open %s ;-;\n", filepath);

		fclose(decoder.filepointer); // Close file
		exit(-1);
	}

	// Read data into libogg & use it to create a page
	ogg_sync_init(&decoder.sync_state);
	audio_buffer = ogg_sync_buffer(&decoder.sync_state, 4096l);
	bytes_read = fread(audio_buffer, sizeof(char), 4096, decoder.filepointer);
	(bytes_read < 4096) ? fprintf(stderr, "ogg_decoder_is_vorbis(): %s too short (early EOF)\n", filepath) : 1;
	fclose(decoder.filepointer); // Close file
	ogg_sync_wrote(&decoder.sync_state, bytes_read);
	if (ogg_sync_pageout(&decoder.sync_state, &decoder.page) != 1) {
		fprintf(stderr, "ogg_decoder_is_vorbis(): %s is not an ogg file\n", filepath);

		// Cleanup remaining data
		ogg_sync_clear(&decoder.sync_state);
		return 0;
	}

	// Initialize data types
	ogg_stream_init(&decoder.stream_state, ogg_page_serialno(&decoder.page));
	vorbis_info_init(&decoder.info);
	vorbis_comment_init(&decoder.comments);

	// Submit packet to vorbis
	ogg_stream_pagein(&decoder.stream_state, &decoder.page);
	ogg_stream_packetout(&decoder.stream_state, &decoder.packet);

	// Check if is vorbis
	if (vorbis_synthesis_headerin(&decoder.info, &decoder.comments, &decoder.packet) < 0 ) {
		fprintf(stderr, "ogg_decoder_is_vorbis(): %s is not an ogg/vorbis file\n", filepath);

		// Cleanup remaining data
		ogg_stream_clear(&decoder.stream_state);
		ogg_sync_clear(&decoder.sync_state);
		vorbis_info_clear(&decoder.info);
		vorbis_comment_clear(&decoder.comments);
		return 0;
	}

	// Cleanup remaining data
	ogg_stream_clear(&decoder.stream_state);
	ogg_sync_clear(&decoder.sync_state);
	vorbis_info_clear(&decoder.info);
	vorbis_comment_clear(&decoder.comments);

	// File is vorbis :)
	return 1;}
