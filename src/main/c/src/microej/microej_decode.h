// Copyright 2021-2026 MicroEJ Corp.
// Use of this source code is governed by a BSD-style license that can be found with this software.
//
// Build: 7E4D1F7C

#ifndef WEBP_MICROEJ_MICROEJ_DECODE_H_
#define WEBP_MICROEJ_MICROEJ_DECODE_H_

#include "LLUI_DISPLAY_impl.h"

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// MicroEJ WEBP decoder entry point

/**
 * @brief Decodes a WebP image into a MicroUI image allocated in the images heap.
 *
 * The decoded image is always in the ARGB8888 format, whatever the expected format.
 *
 * @param[in] addr the address of the encoded WebP image.
 * @param[in] length the size of the encoded WebP image, in bytes.
 * @param[in] expectedFormat the MicroUI image format that the caller expects.
 * @param[out] data the MicroUI image to fill: its size, its format and its buffer.
 * @param[out] isFullyOpaque true when the WebP image has no alpha channel.
 *
 * @return LLUI_DISPLAY_OK on success, LLUI_DISPLAY_OUT_OF_MEMORY when the images heap is full,
 * LLUI_DISPLAY_NOK when the WebP image cannot be decoded.
 */
LLUI_DISPLAY_Status MICROEJ_DECODE_webp(const uint8_t *addr, uint32_t length, MICROUI_ImageFormat expectedFormat,
                                        MICROUI_Image *data, bool *isFullyOpaque);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}    // extern "C"
#endif

#endif  // WEBP_MICROEJ_MICROEJ_DECODE_H_
