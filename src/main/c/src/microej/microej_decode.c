// Copyright 2021-2026 MicroEJ Corp.
// Use of this source code is governed by a BSD-style license that can be found with this software.
//
// Build: 7E4D1F7C

#include "src/microej/microej_decode.h"
#include "src/webp/decode.h"

// -----------------------------------------------------------------------------

LLUI_DISPLAY_Status MICROEJ_DECODE_webp(const uint8_t *addr, uint32_t length, MICROUI_ImageFormat expectedFormat,
                                        MICROUI_Image *data, bool *isFullyOpaque) {

	WebPDecoderConfig config;
	WebPBitstreamFeatures* const bitstream = &config.input;
	LLUI_DISPLAY_Status ret;

	// reset config
	if (!WebPInitDecoderConfig(&config)) {
		ret = LLUI_DISPLAY_NOK;
	}
	else {

		// retrieve image information
		VP8StatusCode status = WebPGetFeatures(addr, length, bitstream);
		if (status != VP8_STATUS_OK) {
			ret = LLUI_DISPLAY_NOK;
		}
		else {

			// every expected format is decoded in ARGB8888 (RGB565 is not functional yet)
			(void)expectedFormat;
			*isFullyOpaque = !(bitstream->has_alpha);

			// fill image data
			data->width = bitstream->width;
			data->height = bitstream->height;
			data->format = MICROUI_IMAGE_FORMAT_ARGB8888;

			// allocate space in images heap
			if (!LLUI_DISPLAY_allocateImageBuffer(data, 0)) {
				ret = LLUI_DISPLAY_OUT_OF_MEMORY;
			}
			else {

				const uint8_t *ret_addr = WebPDecodeBGRAInto(addr, length, LLUI_DISPLAY_getBufferAddress(data),
				                                             LLUI_DISPLAY_getStrideInBytes(data) * data->height,
				                                             LLUI_DISPLAY_getStrideInBytes(data));
				ret = ret_addr != LLUI_DISPLAY_getBufferAddress(data) ? LLUI_DISPLAY_NOK : LLUI_DISPLAY_OK;
			}
		}
	}
	return ret;
}

//------------------------------------------------------------------------------
