# StoneyDSP

The StoneyDSP audio Library.

---
[![windows](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yml)
[![macos](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yml)
[![ubuntu](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml/badge.svg)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yml)

---

## Contents

- [Features](#features)
- [FAQ](#faq)
  - [core](#core)
  - [simd](#simd)
  - [dsp](#dsp)
  - [test](#test)
  - [doc](#doc)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Features

- ### core

  The core features and functionalities of StoneyDSP.

- ### simd

  SIMD data types for optimized performance.

- ### dsp

  The DSP (digital signal processing) features and functionalities of StoneyDSP.

- ### test

	Unit-tests with Catch2.

- ### doc

	Documentation with Doxygen.

## FAQ

- ### When and Why to Use `-DSTONEYDSP_EXPORTS`:

	#### Purpose:

	- The `-DSTONEYDSP_EXPORTS` definition is used to specify that symbols (functions, classes, variables) are being exported from a dynamic library (DLL) rather than imported. This distinction is essential for Windows DLLs because the way symbols are handled differs between exporting and importing.

	#### When to Use:

	- ##### Building the Library:

	When you are compiling the source code of the StoneyDSP library itself, you should define `-DSTONEYDSP_EXPORTS`. This ensures that symbols are marked for export.

	- ##### Using the Library:

	When another project is consuming or using the StoneyDSP library (e.g., linking against the DLL), `-DSTONEYDSP_EXPORTS` should NOT be defined. This ensures that symbols are correctly imported.

	#### Example:

	- ##### Building the Library:

	```sh
	g++ -DSTONEYDSP_EXPORTS -o libstoneydsp.so myLibrary.cpp
	```

	- ##### Using the Library:

	```sh
	g++ -o myApplication main.cpp -lstoneydsp
	```

	This approach helps in maintaining clear boundaries between *exporting* and *importing* symbols, ensuring the correct behavior during linking and execution.

## License

Copyright (C) 2024 Nathan J. Hood <nathanjhood@googlemail.com> MIT License.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
  claim that you wrote the original source code. If you use this source code
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

For more information, visit the website:
[www.stoneydsp.com](https://www.stoneydsp.com)

FULL STONEYDSP TERMS:
- [STONEYDSP END-USER LICENSE AGREEMENT](https://www.stoneydsp.com/licence)
- [STONEYDSP PRIVACY POLICY](https://www.stoneydsp.com/privacy-policy)

## Acknowledgements
