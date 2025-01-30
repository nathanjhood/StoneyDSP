/**
 * @file stoneydsp.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STONEYDSP_H_INCLUDED
#define STONEYDSP_H_INCLUDED

//==============================================================================

#ifndef STONEYDSP_STRINGIFY
  # define STONEYDSP_STRINGIFY_HELPER(n) #n
  /**
   * @brief Handy stringify pre-processor macro.
   * @param n The value to stringify.
   */
  # define STONEYDSP_STRINGIFY(n) STONEYDSP_STRINGIFY_HELPER(n)
#endif

//==============================================================================

#ifdef STONEYDSP_BUILD_CORE
	#include "stoneydsp/core/core.h"
#endif

//==============================================================================

#ifdef STONEYDSP_BUILD_SIMD
// 	#include "stoneydsp/simd/simd.h"
#endif

//==============================================================================

#ifdef STONEYDSP_BUILD_DSP
// #include "stoneydsp/dsp/dsp.h"
#endif

//==============================================================================

// Define wide character support macros
#if STONEYDSP_WINDOWS
  #define STONEYDSP_SUPPORTS_WIDECHARS 1
#else
  #if __cplusplus >= 201103L || (__GNUC__ >= 5)
    #define STONEYDSP_SUPPORTS_WIDECHARS 1
  #endif
#endif

//==============================================================================

// #if STONEYDSP_ARM && STONEYDSP_USING_INT64_2 != 0
//  #define STONEYDSP_USING_INT64_2 1
// #endif

//==============================================================================

#endif // STONEYDSP_H_INCLUDED
