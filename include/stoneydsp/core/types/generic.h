/**
 * @file generic.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED
  #define STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

using byte_t = signed char;
using char_t = signed char;
using short_int_t = signed short int;
using int_t = signed int;
using long_int_t = long int;
using long_long_int_t = signed long long int;

using ubyte_t = unsigned char;
using uchar_t = unsigned char;
using ushort_int_t = unsigned short int;
using uint_t = unsigned int;
using ulong_int_t = unsigned long int;
using ulong_long_int_t = unsigned long long int;

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

extern "C"
{

  typedef ::stoneydsp::byte_t stoneydsp_byte_t;
  typedef ::stoneydsp::char_t stoneydsp_char_t;
  typedef ::stoneydsp::short_int_t stoneydsp_short_int_t;
  typedef ::stoneydsp::int_t stoneydsp_int_t;
  typedef ::stoneydsp::long_int_t stoneydsp_long_int_t;
  typedef ::stoneydsp::long_long_int_t stoneydsp_long_long_int_t;

  typedef ::stoneydsp::ubyte_t stoneydsp_ubyte_t;
  typedef ::stoneydsp::uchar_t stoneydsp_uchar_t;
  typedef ::stoneydsp::ushort_int_t stoneydsp_ushort_int_t;
  typedef ::stoneydsp::uint_t stoneydsp_uint_t;
  typedef ::stoneydsp::ulong_int_t stoneydsp_ulong_int_t;
  typedef ::stoneydsp::ulong_long_int_t stoneydsp_ulong_long_int_t;
}

//==============================================================================

extern "C"
{

  typedef stoneydsp_byte_t stoneydsp_byte;
  typedef stoneydsp_char_t stoneydsp_char;
  typedef stoneydsp_short_int_t stoneydsp_short_int;
  typedef stoneydsp_int_t stoneydsp_int;
  typedef stoneydsp_long_int_t stoneydsp_long_int;
  typedef stoneydsp_long_long_int_t stoneydsp_long_long_int;

  typedef stoneydsp_ubyte_t stoneydsp_ubyte;
  typedef stoneydsp_uchar_t stoneydsp_uchar;
  typedef stoneydsp_ushort_int_t stoneydsp_ushort_int;
  typedef stoneydsp_uint_t stoneydsp_uint;
  typedef stoneydsp_ulong_int_t stoneydsp_ulong_int;
  typedef stoneydsp_ulong_long_int_t stoneydsp_ulong_long_int;
}

//==============================================================================

namespace stoneydsp
{
/** @addtogroup stoneydsp
 *  @{
 */

using byte = ::stoneydsp_char;
using character = ::stoneydsp_char; // char is reserved anyways
using short_int = ::stoneydsp_short_int;
using integer = ::stoneydsp_int;
using long_int = ::stoneydsp_long_int;
using long_long_int = ::stoneydsp_long_long_int;

using ubyte = ::stoneydsp_uchar;
using ucharacter = ::stoneydsp_uchar;
using ushort_int = ::stoneydsp_ushort_int;
using uint = ::stoneydsp_uint;
using ulong_int = ::stoneydsp_ulong_int;
using ulong_long_int = ::stoneydsp_ulong_long_int;

/// @} group stoneydsp
} // namespace stoneydsp

//==============================================================================

#endif // STONEYDSP_CORE_TYPES_GENERIC_H_INCLUDED

//=========================================================================//EOF
