/**
 * @file int.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_INT_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//====================================================================//INCLUDES

  #include <cstdint> // Fixed-width integer types

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 8 signed bits.
 */
using int8_t = ::std::int8_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 8 unsigned bits.
 */
using uint8_t = ::std::uint8_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 16 signed bits.
 */
using int16_t = ::std::int16_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 16 unsigned bits.
 */
using uint16_t = ::std::uint16_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 32 signed bits.
 */
using int32_t = ::std::int32_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 32 unsigned bits.
 */
using uint32_t = ::std::uint32_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 64 signed bits.
 */
using int64_t = ::std::int64_t;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 64 unsigned bits.
 */
using uint64_t = ::std::uint64_t;

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

extern "C"
{

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 8 signed bits.
   */
  typedef stoneydsp::int8_t stoneydsp_int8_t;

  /**
   * @brief Fixed width integer.
   *
   * Guaranteed to be exactly 8 unsigned bits.
   */
  typedef stoneydsp::uint8_t stoneydsp_uint8_t;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 16 signed bits.
   */
  typedef stoneydsp::int16_t stoneydsp_int16_t;

  /**
   * @brief Fixed width integer.
   *
   * Guaranteed to be exactly 16 unsigned bits.
   */
  typedef stoneydsp::uint16_t stoneydsp_uint16_t;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 32 signed bits.
   */
  typedef stoneydsp::int32_t stoneydsp_int32_t;

  /**
   * @brief Fixed width integer.
   *
   * Guaranteed to be exactly 32 unsigned bits.
   */
  typedef stoneydsp::uint32_t stoneydsp_uint32_t;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 64 signed bits.
   */
  typedef stoneydsp::int64_t stoneydsp_int64_t;

  /**
   * @brief Fixed width integer.
   *
   * Guaranteed to be exactly 64 unsigned bits.
   */
  typedef stoneydsp::uint64_t stoneydsp_uint64_t;
}

//==============================================================================

extern "C"
{

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 8 signed bits.
   */
  typedef stoneydsp_int8_t stoneydsp_int8;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 8 unsigned bits.
   */
  typedef stoneydsp_uint8_t stoneydsp_uint8;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 16 signed bits.
   */
  typedef stoneydsp_int16_t stoneydsp_int16;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 16 unsigned bits.
   */
  typedef stoneydsp_uint16_t stoneydsp_uint16;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 32 signed bits.
   */
  typedef stoneydsp_int32_t stoneydsp_int32;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 32 unsigned bits.
   */
  typedef stoneydsp_uint32_t stoneydsp_uint32;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 64 signed bits.
   */
  typedef stoneydsp_int64_t stoneydsp_int64;

  /**
   * @brief Fixed-width integer.
   *
   * Guaranteed to be exactly 64 unsigned bits.
   */
  typedef stoneydsp_uint64_t stoneydsp_uint64;
}

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 8 signed bits.
 */
using int8 = ::stoneydsp_int8;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 8 unsigned bits.
 */
using uint8 = ::stoneydsp_uint8;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 16 signed bits.
 */
using int16 = ::stoneydsp_int16;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 16 unsigned bits.
 */
using uint16 = ::stoneydsp_uint16;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 32 signed bits.
 */
using int32 = ::stoneydsp_int32;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 32 unsigned bits.
 */
using uint32 = ::stoneydsp_uint32;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 64 signed bits.
 */
using int64 = ::stoneydsp_int64;

/**
 * @brief Fixed-width integer.
 *
 * Guaranteed to be exactly 64 unsigned bits.
 */
using uint64 = ::stoneydsp_uint64;

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_INT_H_INCLUDED

//=========================================================================//EOF
