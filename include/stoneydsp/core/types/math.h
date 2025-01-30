/**
 * @file math.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STONEYDSP_CORE_TYPES_MATH_H_INCLUDED
#define STONEYDSP_CORE_TYPES_MATH_H_INCLUDED

//====================================================================//INCLUDES

#include <cmath> // For `float_t` and `double_t`;

//==============================================================================

namespace stoneydsp {
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief Double-precision numerical value.
 *
 */
using double_t = ::double_t;

/**
 * @brief Single-precision numerical value.
 *
 */
using float_t = ::float_t;

  /// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

extern "C" {

/**
 * @brief Double-precision numerical value.
 *
 */
typedef stoneydsp::double_t stoneydsp_double_t;

/**
 * @brief Single-precision numerical value.
 *
 */
typedef stoneydsp::float_t stoneydsp_float_t;

}

//==============================================================================

extern "C" {

/**
 * @brief Double-precision numerical value.
 *
 */
typedef stoneydsp_double_t stoneydsp_double;

/**
 * @brief Single-precision numerical value.
 *
 */
typedef stoneydsp_float_t stoneydsp_float;

}

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_MATH_H_INCLUDED

//=========================================================================//EOF
