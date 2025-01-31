/**
 * @file core.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STONEYDSP_CORE_H_INCLUDED
#define STONEYDSP_CORE_H_INCLUDED

//============================================================================//

/**
 * @brief Internal helper for stringify pre-processor macro.
 * @param n The value to stringify.
 */
# define __STONEYDSP_STRINGIFY_HELPER(n) #n

/**
 * @brief Handy stringify pre-processor macro.
 * @param n The value to stringify.
 */
# define STONEYDSP_STRINGIFY(n) __STONEYDSP_STRINGIFY_HELPER(n)

/* Convert integer to decimal digit literals.  */
#define STONEYDSP_DEC(n)         \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define STONEYDSP_HEX(n)   \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

//============================================================================//

/* tring literal encoding the version number. */
extern char const* stoneydsp_version;

//====================================================================//INCLUDES

#include "stoneydsp/core/system/platform.h"
#include "stoneydsp/core/system/compiler.h"
#include "stoneydsp/core/system/languages.h"
#include "stoneydsp/core/system/cxx.h"

//==============================================================================

#include "stoneydsp/core/types/generic.h"
#include "stoneydsp/core/types/int.h"
#include "stoneydsp/core/types/math.h"

//==============================================================================

#endif // STONEYDSP_CORE_H_INCLUDED

//=========================================================================//EOF
