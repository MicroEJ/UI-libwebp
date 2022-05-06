
# Overview

WebP codec: library to encode and decode images in [WebP format](https://developers.google.com/speed/webp/). 
This package contains the library that can be used in other programs to add WebP support.

This library contains the C library [libwebp](https://chromium.googlesource.com/webm/libwebp).

# Allocation

The default allocator (malloc/calloc) has been replaced by the Graphics Engine's allocator (see utils/utils.c and microej/microej_utils.c).

# Usage

## Platform

Add the following line to the `module.ivy` of your platform configuration project:

    <dependency org="com.microej.clibrary.thirdparty" name="libwebp" rev="1.0.1"/>

## BSP

In the BSP project, add all C files from these folders:

- MicroEJ/thirdparty/libwebp/src/dec
- MicroEJ/thirdparty/libwebp/src/dsp
- MicroEJ/thirdparty/libwebp/src/microej
- MicroEJ/thirdparty/libwebp/src/utils
- MicroEJ/thirdparty/libwebp/src/webp

Add the folder `MicroEJ/thirdparty/libwebp` in the include directories list.

## LLUI_DISPLAY_IMPL

- Add the include directive: `#include "src/microej/microej_decode.h"`.
- Implement the function `LLUI_DISPLAY_Status LLUI_DISPLAY_IMPL_decodeImage(xxx)` (or update it):

```
LLUI_DISPLAY_Status LLUI_DISPLAY_IMPL_decodeImage(uint8_t* addr, uint32_t length, MICROUI_ImageFormat expectedFormat, MICROUI_Image* data, bool* isFullyOpaque)
{
	return MICROEJ_DECODE_webp(addr, length, expectedFormat, data, isFullyOpaque);
}
```

# Requirements

N/A.

# Dependencies

_All dependencies are retrieved transitively by MicroEJ Module Manager_.

# Source

N/A.

# Restrictions

None.

---
_Copyright 2021-2022 MicroEJ Corp. All rights reserved._  
_Use of this source code is governed by a BSD-style license that can be found with this software._  
