/**
 * @file stddef.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-02-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_STDDEF_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_STDDEF_H_INCLUDED

//====================================================================//INCLUDES

// #ifdef __cplusplus
//   #include <cstddef>
// #else
//   #include <stddef.h>
// #endif

  #include <cstddef>

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

namespace core
{
/** @addtogroup core
 *  @{
 */

namespace types
{
/** @addtogroup types
 *  @{
 */

/**
 * @brief An unsigned integer type used to represent the size of objects.
 *
 * Used for array indexing, loop counters, and size calculations.
 */
using size_t = ::std::size_t;

/**
 * @brief A signed integer type used to represent the difference between two
 * pointers.
 *
 * Used for pointer arithmetic and array indexing.
 */
using ptrdiff_t = ::std::ptrdiff_t;

/**
 * @brief The type of the null pointer constant `nullptr`.
 *
 * Used for null pointer assignments and comparisons.
 */
using nullptr_t = ::std::nullptr_t;

/**
 * @brief A type with the maximum alignment requirement for any type on the
 * system.
 *
 * Used to ensure proper memory alignment in data structures
 */
using max_align_t = ::std::max_align_t;

/// @} group types
} // namespace types
/// @} group core
} // namespace core
/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief An unsigned integer type used to represent the size of objects.
 *
 * Used for array indexing, loop counters, and size calculations.
 */
using size_t = ::stoneydsp::core::types::size_t;

/**
 * @brief A signed integer type used to represent the difference between two
 * pointers.
 *
 * Used for pointer arithmetic and array indexing.
 */
using ptrdiff_t = ::stoneydsp::core::types::ptrdiff_t;

/**
 * @brief The type of the null pointer constant `nullptr`.
 *
 * Used for null pointer assignments and comparisons.
 */
using nullptr_t = ::stoneydsp::core::types::nullptr_t;

/**
 * @brief A type with the maximum alignment requirement for any type on the
 * system.
 *
 * Used to ensure proper memory alignment in data structures
 */
using max_align_t = ::stoneydsp::core::types::max_align_t;

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

extern "C"
{
  /**
   * @brief An unsigned integer type used to represent the size of objects.
   *
   * Used for array indexing, loop counters, and size calculations.
   */
  typedef ::stoneydsp::size_t stoneydsp_size_t;

  /**
   * @brief A signed integer type used to represent the difference between two
   * pointers.
   *
   * Used for pointer arithmetic and array indexing.
   */
  typedef ::stoneydsp::ptrdiff_t stoneydsp_ptrdiff_t;

  /**
   * @brief The type of the null pointer constant `nullptr`.
   *
   * Used for null pointer assignments and comparisons.
   */
  typedef ::stoneydsp::nullptr_t stoneydsp_nullptr_t;

  /**
   * @brief A type with the maximum alignment requirement for any type on the
   * system.
   *
   * Used to ensure proper memory alignment in data structures
   */
  typedef ::stoneydsp::max_align_t stoneydsp_max_align_t;
}

//==============================================================================

extern "C"
{
  /**
   * @brief An unsigned integer type used to represent the size of objects.
   *
   * Used for array indexing, loop counters, and size calculations.
   */
  typedef stoneydsp_size_t stoneydsp_size;

  /**
   * @brief A signed integer type used to represent the difference between two
   * pointers.
   *
   * Used for pointer arithmetic and array indexing.
   */
  typedef stoneydsp_ptrdiff_t stoneydsp_ptrdiff;

  /**
   * @brief The type of the null pointer constant `nullptr`.
   *
   * Used for null pointer assignments and comparisons.
   */
  typedef stoneydsp_nullptr_t stoneydsp_nullptr;

  /**
   * @brief A type with the maximum alignment requirement for any type on the
   * system.
   *
   * Used to ensure proper memory alignment in data structures
   */
  typedef stoneydsp_max_align_t stoneydsp_max_align;
}

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_STDDEF_H_INCLUDED

//=========================================================================//EOF
