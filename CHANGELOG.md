# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.5] - 2026-10-07

### Changed

- Apply the change of `utils.c` from a patch, `src/main/patch/utils.c.patch`, which the README describes for an integration from the GitHub repository; the archive does not change.
- List in the README the boards this C Module is tested on and the MISRA deviations of its support files, which cppcheck now checks.

### Fixed

- Fix the MISRA deviations of the decoder entry point and of the allocator, with no change of behavior; `MICROEJ_DECODE_webp` now takes a `const` encoded image address.

## [1.0.4] - 2026-10-06

### Changed

- Update the license.
- Complete the Doxygen documentation of the decoder entry point, and align the README with the other MicroEJ C modules.

## [1.0.3] - 2023-05-03

### Fixed

- Fix an include directive for case-sensitive filesystems.

## [1.0.2] - 2022-06-08

### Changed

- Remove useless files.
- Explain the modification in `utils.c`.

### Fixed

- Fix the README file.
  
## [1.0.1] - 2022-05-06

### Added

- Add the libwebp's files: AUTHORS, COPYING and PATENTS.

## [1.0.0] - 2022-05-05

### Added

- Initial revision: fetch [libwebp](https://chromium.googlesource.com/webm/libwebp).
- Replace the default allocator by the Graphics Engine's allocator.
- Add the MicroEJ image decoder entry point.

---
_Copyright 2021-2026 MicroEJ Corp._\
_Use of this source code is governed by a BSD-style license that can be found with this software._\
_Build: 7E4D1F7C_
