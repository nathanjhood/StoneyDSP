/***************************************************************************//**
 * @file stoneydsp_version.h
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @brief Versions with the same major number are ABI stable. API is allowed to
 * evolve between minor releases, but only in a backwards compatible way.
 * Make sure you update the -soname directives in configure.ac
 * whenever you bump STONEYDSP_VERSION_MAJOR or STONEYDSP_VERSION_MINOR (but
 * not STONEYDSP_VERSION_PATCH.)
 * @version 0.1
 * @date 2023-09-09
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#define STONEYDSP_CORE_VERSION_H_INCLUDED

#ifndef STRINGIFY
# define STRINGIFY_HELPER(n) #n
# define STRINGIFY(n) STRINGIFY_HELPER(n)
#endif

#define STONEYDSP_COPYRIGHT "Nathan J. Hood <nathanjhood@googlemail.com>"

#ifndef STONEYDSP_VERSION_MAJOR
 #define STONEYDSP_VERSION_MAJOR 1
#endif

#ifndef STONEYDSP_VERSION_MINOR
 #define STONEYDSP_VERSION_MINOR 0
#endif

#ifndef STONEYDSP_VERSION_PATCH
 #define STONEYDSP_VERSION_PATCH 0
#endif

#ifndef STONEYDSP_VERSION_TWEAK
 #define STONEYDSP_VERSION_TWEAK STRINGIFY(-pre)
#endif

#define STONEYDSP_VERSION_IS_RELEASE 1
#define STONEYDSP_VERSION_SUFFIX ""

#define STONEYDSP_VERSION_HEX \
    ((STONEYDSP_VERSION_MAJOR << 16) | \
     (STONEYDSP_VERSION_MINOR <<  8) | \
     (STONEYDSP_VERSION_PATCH))

/**
 * @brief major * 10000 + minor * 100 + patch.
 *
 */
#define STONEYDSP_VERSION_LONG ((STONEYDSP_VERSION_MAJOR * 10000) + (STONEYDSP_VERSION_MINOR * 100) + STONEYDSP_VERSION_PATCH)

/**
 * @brief "major.minor.patch-tweak"
 *
 */
#define STONEYDSP_VERSION_STRING \
    STRINGIFY(STONEYDSP_VERSION_MAJOR) STRINGIFY(.) \
    STRINGIFY(STONEYDSP_VERSION_MINOR) STRINGIFY(.) \
    STRINGIFY(STONEYDSP_VERSION_PATCH) STRINGIFY(-) \
    STRINGIFY(STONEYDSP_VERSION_TWEAK)
