/**
 * @file version.h
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef STONEYDSP_VERSION_H
#define STONEYDSP_VERSION_H

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

#endif // STONEYDSP_VERSION_H
