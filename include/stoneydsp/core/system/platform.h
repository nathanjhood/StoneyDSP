/**
 * @file platform.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STONEYDSP_CORE_SYSTEM_PLATFORM_H_INCLUDED
#define STONEYDSP_CORE_SYSTEM_PLATFORM_H_INCLUDED

//==============================================================================

/**
 * The following pre-processor macros come from the JUCE v7 library's
 * 'juce_core' module, which is licensed under the  GNU General Public
 * License v.3.
 *
 * The code has been shamefully hoisted here, in order to be utilized within
 * the StoneyDSP codebase in a way which best ensures compatibility with
 * JUCE *and* with other audio software libraries.
 *
 * This file figures out which platform is being built, and defines some
 * macros that the rest of the code can use for OS-specific compilation.
 *
 * Macros that will be set here are:
 *
 * - One of STONEYDSP_WINDOWS, STONEYDSP_MAC STONEYDSP_LINUX, STONEYDSP_IOS,
 * STONEYDSP_ANDROID, etc.
 * - Either STONEYDSP_32BIT or STONEYDSP_64BIT, depending on the architecture.
 * - Either STONEYDSP_LITTLE_ENDIAN or STONEYDSP_BIG_ENDIAN.
 * - Either STONEYDSP_INTEL or STONEYDSP_ARM
 * - Either STONEYDSP_GCC or STONEYDSP_CLANG or STONEYDSP_MSVC
 */

//==============================================================================
#if defined (_WIN32) || defined (_WIN64)
  #define       STONEYDSP_WINDOWS 1
#elif defined (STONEYDSP_ANDROID)
  #undef        STONEYDSP_ANDROID
  #define       STONEYDSP_ANDROID 1
#elif defined (__FreeBSD__) || defined (__OpenBSD__)
  #define       STONEYDSP_BSD 1
#elif defined (LINUX) || defined (__linux__)
  #define       STONEYDSP_LINUX 1
#elif defined (__APPLE_CPP__) || defined (__APPLE_CC__)
  #define CF_EXCLUDE_CSTD_HEADERS 1
  #include <TargetConditionals.h> // (needed to find out what platform we're using)
  #include <AvailabilityMacros.h>

  #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    #define     STONEYDSP_IPHONE 1
    #define     STONEYDSP_IOS 1
  #else
    #define     STONEYDSP_MAC 1
  #endif
#elif defined (__wasm__)
  #define       STONEYDSP_WASM 1
#else
  #error "Unknown platform!"
#endif

//==============================================================================

#if STONEYDSP_WINDOWS
  #ifdef _MSC_VER
    #ifdef _WIN64
      #define STONEYDSP_64BIT 1
    #else
      #define STONEYDSP_32BIT 1
    #endif
  #endif

  #ifdef _DEBUG
    #define STONEYDSP_DEBUG 1
  #endif

  #ifdef __MINGW32__
    #define STONEYDSP_MINGW 1
    #ifdef __MINGW64__
      #define STONEYDSP_64BIT 1
    #else
      #define STONEYDSP_32BIT 1
    #endif
  #endif

  /** If defined, this indicates that the processor is little-endian. */
  #define STONEYDSP_LITTLE_ENDIAN 1

  #if defined (_M_ARM) || defined (_M_ARM64) || defined (__arm__) || defined (__aarch64__)
    #define STONEYDSP_ARM 1
  #else
    #define STONEYDSP_INTEL 1
  #endif
#endif

//==============================================================================

#if STONEYDSP_MAC || STONEYDSP_IOS

  #if defined (DEBUG) || defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
    #define STONEYDSP_DEBUG 1
  #endif

  #if ! (defined (DEBUG) || defined (_DEBUG) || defined (NDEBUG) || defined (_NDEBUG))
    #warning "Neither NDEBUG or DEBUG has been defined - you should set one of these to make it clear whether this is a release build,"
  #endif

  #ifdef __LITTLE_ENDIAN__
    #define STONEYDSP_LITTLE_ENDIAN 1
  #else
    #define STONEYDSP_BIG_ENDIAN 1
  #endif

  #ifdef __LP64__
    #define STONEYDSP_64BIT 1
  #else
    #define STONEYDSP_32BIT 1
  #endif

  #if defined (__ppc__) || defined (__ppc64__)
    #error "PowerPC is no longer supported by STONEYDSP!"
  #elif defined (__arm__) || defined (__arm64__)
    #define STONEYDSP_ARM 1
  #else
    #define STONEYDSP_INTEL 1
  #endif

  #if STONEYDSP_MAC
    #if ! defined (MAC_OS_X_VERSION_10_14)
      #error "The 10.14 SDK (Xcode 10.1+) is required to build STONEYDSP apps. You can create apps that run on macOS 10.9+ by changing the deployment target."
    #elif MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_9
      #error "Building for OSX 10.8 and earlier is no longer supported!"
    #endif
  #endif
#endif

//==============================================================================

#if STONEYDSP_LINUX || STONEYDSP_ANDROID || STONEYDSP_BSD

  #ifdef _DEBUG
    #define STONEYDSP_DEBUG 1
  #endif

  // Allow override for big-endian Linux platforms
  #if defined (__LITTLE_ENDIAN__) || ! defined (STONEYDSP_BIG_ENDIAN)
    #define STONEYDSP_LITTLE_ENDIAN 1
    #undef STONEYDSP_BIG_ENDIAN
  #else
    #undef STONEYDSP_LITTLE_ENDIAN
    #define STONEYDSP_BIG_ENDIAN 1
  #endif

  #if defined (__LP64__) || defined (_LP64) || defined (__arm64__)
    #define STONEYDSP_64BIT 1
  #else
    #define STONEYDSP_32BIT 1
  #endif

  #if defined (__arm__) || defined (__arm64__) || defined (__aarch64__)
    #define STONEYDSP_ARM 1
  #elif __MMX__ || __SSE__ || __amd64__
    #define STONEYDSP_INTEL 1
  #endif
#endif

//==============================================================================

#endif // STONEYDSP_CORE_SYSTEM_PLATFORM_H_INCLUDED

//==============================================================================
