# Overview

This C Module decodes the images in [WebP format](https://developers.google.com/speed/webp/) at runtime, in a VEE Port that uses the MicroEJ UI Pack.
It integrates the C library [libwebp](https://chromium.googlesource.com/webm/libwebp) and provides the entry point that the Graphics Engine calls to decode an image.
See [Additional Decoders](https://docs.microej.com/en/latest/VEEPortingGuide/uiImageLoader.html#additional-decoders) and [Original Input Format](https://docs.microej.com/en/latest/VEEPortingGuide/uiImageRaw.html#original-input-format) in the MicroEJ documentation.

# Usage

1. Add the sources of this C Module to the BSP of the VEE Port, in either of these two ways:

   - From the MicroEJ repository: install the `.cco` archive of the version the VEE Port needs, as the [installation guide](https://docs.microej.com/en/latest/VEEPortingGuide/appendix/cmodules.html) describes.
     The archive holds the libwebp source, with the patch of this C Module applied, and the support files, in `bsp/thirdparty/libwebp`.
   - From GitHub: add the [GitHub repository](https://github.com/MicroEJ/UI-libwebp) to the BSP of the VEE Port as a git submodule, at the tag of the version the VEE Port needs.
     The repository holds the support files only, in `<folder>/src/main/c/src/microej`, where `<folder>` is the folder of the submodule.
     Get the libwebp source at the commit `8ea81561d2fdd382da60f57958741a7c23a18eb6`, 31 commits after the tag `v1.2.1`, apply the patch of this C Module to it, then copy the files this C Module uses in `<folder>/src/main/c`, the folder the support files expect:

     ```sh
     git submodule add https://github.com/MicroEJ/UI-libwebp.git bsp/vee/port/ui/UI-libwebp
     git -C bsp/vee/port/ui/UI-libwebp checkout <version>
     git clone https://chromium.googlesource.com/webm/libwebp libwebp-upstream
     git -C libwebp-upstream checkout 8ea81561d2fdd382da60f57958741a7c23a18eb6
     git -C libwebp-upstream apply ../bsp/vee/port/ui/UI-libwebp/src/main/patch/utils.c.patch
     (cd libwebp-upstream && cp --parents src/dec/*.[ch] src/dsp/*.[ch] src/enc/*.h src/utils/*.[ch] src/webp/*.h AUTHORS COPYING PATENTS ../bsp/vee/port/ui/UI-libwebp/src/main/c/)
     rm -f bsp/vee/port/ui/UI-libwebp/src/main/c/src/dsp/*mips* bsp/vee/port/ui/UI-libwebp/src/main/c/src/dsp/*neon* bsp/vee/port/ui/UI-libwebp/src/main/c/src/dsp/*sse2* bsp/vee/port/ui/UI-libwebp/src/main/c/src/dsp/*sse41* bsp/vee/port/ui/UI-libwebp/src/main/c/src/dsp/*msa*
     ```

     The files this C Module uses are the C files and the headers of `src/dec`, of `src/dsp` without the SIMD files (`mips`, `neon`, `sse2`, `sse41` and `msa`), and of `src/utils`, the headers of `src/enc` and of `src/webp`, and the files `AUTHORS`, `COPYING` and `PATENTS`.
     A copy of these sources in the VEE Port repository works as well.

   In the next steps, `<c>` is the folder that holds `src/microej` and the libwebp `src` folders: `bsp/thirdparty/libwebp` for the archive, and `<folder>/src/main/c` for the GitHub repository.

2. In the BSP project, add all C files from these folders:

    - `<c>/src/dec`
    - `<c>/src/dsp`
    - `<c>/src/microej`
    - `<c>/src/utils`
    - `<c>/src/webp`

  Add the folder `<c>` in the include directories list.

3. In the implementation of `LLUI_DISPLAY_impl.h`, add the include directive `#include "src/microej/microej_decode.h"`, and implement the function `LLUI_DISPLAY_IMPL_decodeImage` (or update it):

```
LLUI_DISPLAY_Status LLUI_DISPLAY_IMPL_decodeImage(uint8_t *addr, uint32_t length, jbyte expectedFormat, MICROUI_Image *image, bool *isFullyOpaque)
{
	return MICROEJ_DECODE_webp(addr, length, (MICROUI_ImageFormat)expectedFormat, image, isFullyOpaque);
}
```

4. To use the WebP images in the Simulator and in the Image Generator too, add the tool `com.microej.tool:imageio-webp` to the VEE Port configuration project, at the version that [Original Input Format](https://docs.microej.com/en/latest/VEEPortingGuide/uiImageRaw.html#original-input-format) names in the MicroEJ documentation.
  With SDK 6, declare it in the `build.gradle.kts` of the VEE Port configuration project:

    dependencies {
        microejTool("com.microej.tool:imageio-webp:<version>")
    }

  With SDK 5, add the following line to its `module.ivy` instead:

    <dependency org="com.microej.tool" name="imageio-webp" rev="<version>"/>

# Requirements

None.

# Validation

This C Module is tested with the MicroUI Abstraction Layer on the following boards:

- MIMXRT595-EVK.
- STM32F429I-EVAL.
- STM32U5A9J-DK.
- Linux.

# MISRA Compliance

The support files, in `src/microej`, of this C Module are MISRA-compliant (MISRA C:2012) with some noted exceptions.
The libwebp sources are not checked.
They have been verified with Cppcheck v2.19.
Here is the list of deviations from the MISRA standard:

| Deviation  | Category  | Justification |
|:----------:|:---------:|:------------- |
| Rule 8.7   | Advisory  | The `WebPSafe*` functions require external linkage: they replace the allocator that libwebp calls. |
| Rule 11.5  | Advisory  | A `void *` is converted to the pointer type that the images heap functions take. |
| Rule 17.3  | Mandatory | The implicitly declared functions are the UI Pack's functions. |

# Dependencies

- The MicroUI Abstraction Layer: libwebp allocates its memory in the MicroUI images heap.

# Changelog

The changes of this C Module are listed in the [CHANGELOG](CHANGELOG.md) of this repository.

# Source

- ``microej/microej_decode.h``, ``microej/microej_decode.c``: the decoder entry point, `MICROEJ_DECODE_webp`.
- ``microej/microej_utils.c``: the libwebp allocator (`WebPSafeMalloc`, `WebPSafeCalloc`, `WebPSafeFree`) over the MicroUI images heap, which replaces the `malloc` and `calloc` allocator of ``utils/utils.c``.
- ``dec/``, ``dsp/``, ``utils/``, ``webp/``: the decoding sources of libwebp.
- ``utils/utils.c``: the libwebp file that the patch ``src/main/patch/utils.c.patch`` of the GitHub repository changes, to add a MicroEJ header and to rename ``WebPSafe*`` to ``_WebPSafe*``.

# Restrictions

- This C Module decodes the WebP images, it does not encode them.
- The decoded image is always in the ARGB8888 format.

---
_Copyright 2021-2026 MicroEJ Corp._\
_Use of this source code is governed by a BSD-style license that can be found with this software._\
_Build: 7E4D1F7C_
