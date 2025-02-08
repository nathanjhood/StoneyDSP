/**
 * @file int.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/int.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST)

//==============================================================================

  #include <catch2/catch_test_macros.hpp>

//==============================================================================

  #include "stoneydsp/core/types/math.h" // for `stoneydsp::float_t`

//==============================================================================

  #include <limits>      // for `std::numeric_limits`
  #include <sstream>     // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`

//==============================================================================

// Test tags provided by this file:
//
// [int8]
// [int16]
// [int32]
// [int64]
//
// [uint8]
// [uint16]
// [uint32]
// [uint64]
//
// [sizeof]
// [alignof]
//
// [type_traits]
// [is_signed]
// [is_unsigned]
// [is_trivially_copyable]
// [is_standard_layout]
//
// [numeric_limits]
// [endianness]
// [conversion]
// [special_values]
// [arithmetic]
//
// [serialization]
// [boundary]
// [overflow]

//==============================================================================

namespace stoneydsp
{
/**
 * @brief The `test` namespace.
 *
 * This namespace contains function definitions to be used for unit testing.
 *
 */
namespace test
{

/**
 * @brief
 *
 * @tparam T
 * @param expectedSizeof
 *
 */
template <typename T>
void STONEYDSP_PUBLIC_FUNCTION
testSizeof (const T &expectedSizeof)
{
  REQUIRE (sizeof (T) == expectedSizeof);
}

/**
 * @brief
 *
 * @tparam T
 * @param originalValue
 *
 */
template <typename T>
void STONEYDSP_PUBLIC_FUNCTION
testSerialization (const T &originalValue)
{
  ::std::stringstream ss;
  T deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

} // namespace stoneydsp
} // namespace test

//======================================================================//sizeof

// Ensure types have the expected size across different architectures.

TEST_CASE ("sizeof stoneydsp::int8 is 1 byte", "[sizeof][int8]")
{
  REQUIRE (sizeof (::stoneydsp::int8) == (unsigned long)1UL);
}

TEST_CASE ("sizeof stoneydsp::int16 is 2 bytes", "[sizeof][int16]")
{
  REQUIRE (sizeof (::stoneydsp::int16) == (unsigned long)2UL);
}

TEST_CASE ("sizeof stoneydsp::int32 is 4 bytes", "[sizeof][int32]")
{
  REQUIRE (sizeof (::stoneydsp::int32) == (unsigned long)4UL);
}

TEST_CASE ("sizeof stoneydsp::int64 is 8 bytes", "[sizeof][int64]")
{
  REQUIRE (sizeof (::stoneydsp::int64) == (unsigned long)8UL);
}

//=====================================================================//alignof

// Ensure types have the expected alignment across different architectures.

TEST_CASE ("alignof stoneydsp::int8 is 1 byte", "[alignof][int8]")
{
  REQUIRE (alignof (::stoneydsp::int8) == (unsigned long)1UL);
}

TEST_CASE ("alignof stoneydsp::int16 is 2 bytes", "[alignof][int16]")
{
  REQUIRE (alignof (::stoneydsp::int16) == (unsigned long)2UL);
}

TEST_CASE ("alignof stoneydsp::int32 is 4 bytes", "[alignof][int32]")
{
  REQUIRE (alignof (::stoneydsp::int32) == (unsigned long)4UL);
}

TEST_CASE ("alignof stoneydsp::int64 is 8 bytes", "[alignof][int64]")
{
  REQUIRE (alignof (::stoneydsp::int64) == (unsigned long)8UL);
}

//=================================================================//type_traits

// Ensure types have the expected signedness across different architectures.

TEST_CASE ("Signed-ness of stoneydsp::int8 is positive",
           "[type_traits][is_signed][int8]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int8>::value);
}

TEST_CASE ("Signed-ness of stoneydsp::int16 is positive",
           "[type_traits][is_signed][int16]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int16>::value);
}

TEST_CASE ("Signed-ness of stoneydsp::int32 is positive",
           "[type_traits][is_signed][int32]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int32>::value);
}

TEST_CASE ("Signed-ness of stoneydsp::int64 is positive",
           "[type_traits][is_signed][int64]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int64>::value);
}

//=======================================================//is_trivially_copyable

TEST_CASE ("Is stoneydsp::int8 trivially copyable",
           "[type_traits][is_trivially_copyable][int8]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int8>::value);
}

TEST_CASE ("Is stoneydsp::int16 trivially copyable",
           "[type_traits][is_trivially_copyable][int16]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int16>::value);
}

TEST_CASE ("Is stoneydsp::int32 trivially copyable",
           "[type_traits][is_trivially_copyable][int32]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int32>::value);
}

TEST_CASE ("Is stoneydsp::int64 trivially copyable",
           "[type_traits][is_trivially_copyable][int64]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int64>::value);
}

//==========================================================//is_standard_layout

TEST_CASE ("Is stoneydsp::int8 standard-layout conforming",
           "[type_traits][is_standard_layout][int8]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int8>::value);
}

TEST_CASE ("Is stoneydsp::int16 standard-layout conforming",
           "[type_traits][is_standard_layout][int16]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int16>::value);
}

TEST_CASE ("Is stoneydsp::int32 standard-layout conforming",
           "[type_traits][is_standard_layout][int32]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int32>::value);
}

TEST_CASE ("Is stoneydsp::int64 standard-layout conforming",
           "[type_traits][is_standard_layout][int64]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int64>::value);
}

//==============================================================//numeric_limits

// Ensure that your types handle their minimum and maximum values correctly.

TEST_CASE ("Numeric limits of stoneydsp::int8", "[numeric_limits][int8]")
{
  REQUIRE (::stoneydsp::int8{ -128 }
           == ::std::numeric_limits< ::stoneydsp::int8>::min ());
  REQUIRE (::stoneydsp::int8{ 127 }
           == ::std::numeric_limits< ::stoneydsp::int8>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int16", "[numeric_limits][int16]")
{
  REQUIRE (::stoneydsp::int16{ -32768 }
           == ::std::numeric_limits< ::stoneydsp::int16>::min ());
  REQUIRE (::stoneydsp::int16{ 32767 }
           == ::std::numeric_limits< ::stoneydsp::int16>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int32", "[numeric_limits][int32]")
{
  REQUIRE (::stoneydsp::int32{ -2147483648 }
           == ::std::numeric_limits< ::stoneydsp::int32>::min ());
  REQUIRE (::stoneydsp::int32{ 2147483647 }
           == ::std::numeric_limits< ::stoneydsp::int32>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int64", "[numeric_limits][int64]")
{
  REQUIRE (::stoneydsp::int64{ -9223372036854775807LL - 1 }
           == ::std::numeric_limits< ::stoneydsp::int64>::min ());
  REQUIRE (::stoneydsp::int64{ 9223372036854775807LL }
           == ::std::numeric_limits< ::stoneydsp::int64>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int8", "[endianness][int8]")
{
  ::stoneydsp::int8 value = 0x12;
  ::std::int8_t byte = reinterpret_cast< ::std::uint8_t *> (&value)[0];

  if (byte == 0x12)
    {
      REQUIRE (true); // Little-endian and Big-endian will look the same for a
                      // single byte
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::int16", "[endianness][int16]")
{
  ::stoneydsp::int16 value = 0x1234;
  ::std::uint8_t byte = reinterpret_cast< ::std::uint8_t *> (&value)[0];

  if (byte == 0x34)
    {
      REQUIRE (true); // Little-endian
    }
  else if (byte == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::int32", "[endianness][int32]")
{
  ::stoneydsp::int32 value = 0x12345678;
  ::std::uint8_t byte = reinterpret_cast< ::std::uint8_t *> (&value)[0];

  if (byte == 0x78)
    {
      REQUIRE (true); // Little-endian
    }
  else if (byte == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::int64", "[endianness][int64]")
{
  ::stoneydsp::int64 value = 0x123456789ABCDEF0ULL;
  ::std::uint8_t byte = reinterpret_cast< ::std::uint8_t *> (&value)[0];

  if (byte == 0xF0)
    {
      REQUIRE (true); // Little-endian
    }
  else if (byte == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::int8_t", "[rounding][int8]")
{
  ::stoneydsp::float_t a = -1.5f;
  ::stoneydsp::int8 b = static_cast< ::stoneydsp::int8> (::std::round (a));
  REQUIRE (b == -2); // -1.5 rounded to nearest integer and cast to int8

  a = 1.5f;
  b = static_cast< ::stoneydsp::int8> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int8
}

TEST_CASE ("Rounding behavior of stoneydsp::int16", "[rounding][int16]")
{
  ::stoneydsp::float_t a = -1.5f;
  ::stoneydsp::int16 b = static_cast< ::stoneydsp::int16> (std::round (a));
  REQUIRE (b == -2); // -1.5 rounded to nearest integer and cast to int16

  a = 1.5f;
  b = static_cast< ::stoneydsp::int16> (std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int16
}

TEST_CASE ("Rounding behavior of stoneydsp::int32", "[rounding][int32]")
{
  ::stoneydsp::double_t a = -1.5;
  ::stoneydsp::int32 b = static_cast< ::stoneydsp::int32> (::std::round (a));
  REQUIRE (b == -2); // -1.5 rounded to nearest integer and cast to int32

  a = 1.5;
  b = static_cast< ::stoneydsp::int32> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int32
}

TEST_CASE ("Rounding behavior of stoneydsp::int64", "[rounding][int64]")
{
  ::stoneydsp::double_t a = -1.5;
  ::stoneydsp::int64 b = static_cast< ::stoneydsp::int64> (::std::round (a));
  REQUIRE (b == -2); // -1.5 rounded to nearest integer and cast to int64

  a = 1.5;
  b = static_cast< ::stoneydsp::int64> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int64
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::int8",
           "[numeric_limits][special_values][int8]")
{
  ::stoneydsp::int8 min_val
      = ::std::numeric_limits< ::stoneydsp::int8>::min ();
  ::stoneydsp::int8 max_val
      = ::std::numeric_limits< ::stoneydsp::int8>::max ();
  REQUIRE (min_val == -128); // Minimum value for int8
  REQUIRE (max_val == 127);  // Maximum value for int8
}

TEST_CASE ("Special values of stoneydsp::int16",
           "[numeric_limits][special_values][int16]")
{
  ::stoneydsp::int16 min_val
      = ::std::numeric_limits< ::stoneydsp::int16>::min ();
  ::stoneydsp::int16 max_val
      = ::std::numeric_limits< ::stoneydsp::int16>::max ();
  REQUIRE (min_val == -32768); // Minimum value for int16
  REQUIRE (max_val == 32767);  // Maximum value for int16
}

TEST_CASE ("Special values of stoneydsp::int32",
           "[numeric_limits][special_values][int32]")
{
  ::stoneydsp::int32 min_val
      = ::std::numeric_limits< ::stoneydsp::int32>::min ();
  ::stoneydsp::int32 max_val
      = ::std::numeric_limits< ::stoneydsp::int32>::max ();
  REQUIRE (min_val == -2147483648); // Minimum value for int32
  REQUIRE (max_val == 2147483647);  // Maximum value for int32
}

TEST_CASE ("Special values of stoneydsp::int64",
           "[numeric_limits][special_values][int64]")
{
  ::stoneydsp::int64 min_val
      = ::std::numeric_limits< ::stoneydsp::int64>::min ();
  ::stoneydsp::int64 max_val
      = ::std::numeric_limits< ::stoneydsp::int64>::max ();
  REQUIRE (min_val == -9223372036854775807LL - 1); // Minimum value for int64
  REQUIRE (max_val == 9223372036854775807LL);      // Maximum value for int64
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::int8", "[arithmetic][int8]")
{
  ::stoneydsp::int8 a = 15;
  ::stoneydsp::int8 b = 20;
  REQUIRE (a + b == 35);  // Addition
  REQUIRE (a - b == -5);  // Subtraction
  REQUIRE (a * b == 300); // Multiplication
  REQUIRE (b / a == 1);   // Division
  REQUIRE (b % a == 5);   // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::int16",
           "[arithmetic][int16]")
{
  ::stoneydsp::int16 a = 1500;
  ::stoneydsp::int16 b = 2000;
  REQUIRE (a + b == 3500);    // Addition
  REQUIRE (a - b == -500);    // Subtraction
  REQUIRE (a * b == 3000000); // Multiplication
  REQUIRE (b / a == 1);       // Division
  REQUIRE (b % a == 500);     // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::int32",
           "[arithmetic][int32]")
{
  ::stoneydsp::int32 a = 15000;
  ::stoneydsp::int32 b = 20000;
  REQUIRE (a + b == 35000);     // Addition
  REQUIRE (a - b == -5000);     // Subtraction
  REQUIRE (a * b == 300000000); // Multiplication
  REQUIRE (b / a == 1);         // Division
  REQUIRE (b % a == 5000);      // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::int64",
           "[arithmetic][int64]")
{
  ::stoneydsp::int64 a = 1500000000LL;
  ::stoneydsp::int64 b = 2000000000LL;
  REQUIRE (a + b == 3500000000LL);          // Addition
  REQUIRE (a - b == -500000000LL);          // Subtraction
  REQUIRE (a * b == 3000000000000000000LL); // Multiplication
  REQUIRE (b / a == 1);                     // Division
  REQUIRE (b % a == 500000000LL);           // Modulo
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int8",
           "[serialization][int8]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::int8> (-123);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int16",
           "[serialization][int16]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::int16> (-12345);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int32",
           "[serialization][int32]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::int32> (-123456789);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int64",
           "[serialization][int64]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::int64> (
      -1234567890123456789LL);
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int8",
           "[boundary][underflow][int8]")
{
  ::stoneydsp::int8 a = -128;
  ::stoneydsp::int8 b = 1;
  // cast to prevent integer promition to larger type
  REQUIRE (static_cast< ::stoneydsp::int8> (a - b)
           == 127); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int16",
           "[boundary][underflow][int16]")
{
  ::stoneydsp::int16 a = -32768;
  ::stoneydsp::int16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int16> (a - b)
           == 32767); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int32",
           "[boundary][underflow][int32]")
{
  ::stoneydsp::int32 a = -2147483648;
  ::stoneydsp::int32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int32> (a - b)
           == 2147483647); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int64",
           "[boundary][underflow][int64]")
{
  ::stoneydsp::int64 a = std::numeric_limits< ::stoneydsp::int64>::min ();
  ::stoneydsp::int64 b = 1;
  REQUIRE (
      static_cast< ::stoneydsp::int64> (a - b)
      == std::numeric_limits<
          ::stoneydsp::int64>::max ()); // Check underflow wrap-around behavior
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behavior of stoneydsp::int8",
           "[boundary][overflow][int8]")
{
  ::stoneydsp::int8 a = 127;
  ::stoneydsp::int8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int8> (a + b)
           == -128); // Check overflow behavior
}

TEST_CASE ("Boundary and overflow behavior of stoneydsp::int16",
           "[boundary][overflow][int16]")
{
  ::stoneydsp::int16 a = 32767;
  ::stoneydsp::int16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int16> (a + b)
           == -32768); // Check overflow behavior
}

TEST_CASE ("Boundary and overflow behavior of stoneydsp::int32",
           "[boundary][overflow][int32]")
{
  ::stoneydsp::int32 a = 2147483647;
  ::stoneydsp::int32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int32> (a + b)
           == -2147483648); // Check overflow behavior
}

TEST_CASE ("Boundary and overflow behavior of stoneydsp::int64",
           "[boundary][overflow][int64]")
{
  ::stoneydsp::int64 a = 9223372036854775807LL;
  ::stoneydsp::int64 b = 1;
  REQUIRE (
      static_cast< ::stoneydsp::int64> (a + b)
      == std::numeric_limits< ::stoneydsp::int64>::min ()); // Check overflow
                                                            // behavior
}

//======================================================================//sizeof

// Ensure types have the expected size across different architectures.

TEST_CASE ("sizeof stoneydsp::uint8 is 1 byte", "[sizeof][uint8]")
{
  ::stoneydsp::test::testSizeof< ::stoneydsp::uint8> ((unsigned long)1UL);
}

TEST_CASE ("sizeof stoneydsp::uint16 is 2 bytes", "[sizeof][uint16]")
{
  ::stoneydsp::test::testSizeof< ::stoneydsp::uint16> ((unsigned long)2UL);
}

TEST_CASE ("sizeof stoneydsp::uint32 is 4 bytes", "[sizeof][uint32]")
{
  ::stoneydsp::test::testSizeof< ::stoneydsp::uint32> ((unsigned long)4UL);
}

TEST_CASE ("sizeof stoneydsp::uint64 is 8 bytes", "[sizeof][uint64]")
{
  ::stoneydsp::test::testSizeof< ::stoneydsp::uint64> ((unsigned long)8UL);
}

//=====================================================================//alignof

// Ensure types have the expected alignment across different architectures.

TEST_CASE ("alignof stoneydsp::uint8 is 1 byte", "[alignof][uint8]")
{
  REQUIRE (alignof (::stoneydsp::uint8) == (unsigned long)1UL);
}

TEST_CASE ("alignof stoneydsp::uint16 is 2 bytes", "[alignof][uint16]")
{
  REQUIRE (alignof (::stoneydsp::uint16) == (unsigned long)2UL);
}

TEST_CASE ("alignof stoneydsp::uint32 is 4 bytes", "[alignof][uint32]")
{
  REQUIRE (alignof (::stoneydsp::uint32) == (unsigned long)4UL);
}

TEST_CASE ("alignof stoneydsp::uint64 is 8 bytes", "[alignof][uint64]")
{
  REQUIRE (alignof (::stoneydsp::uint64) == (unsigned long)8UL);
}

//=================================================================//type_traits

// Ensure types have the expected signedness across different architectures.

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint8]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint8>::value);
}

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint16]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint16>::value);
}

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint32]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint32>::value);
}

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint64]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint64>::value);
}

//=======================================================//is_trivially_copyable

TEST_CASE ("Is stoneydsp::uint8 trivially copyable",
           "[type_traits][is_trivially_copyable][uint8]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint8>::value);
}

TEST_CASE ("Is stoneydsp::uint16 trivially copyable",
           "[type_traits][is_trivially_copyable][uint16]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint16>::value);
}

TEST_CASE ("Is stoneydsp::uint32 trivially copyable",
           "[type_traits][is_trivially_copyable][uint32]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint32>::value);
}

TEST_CASE ("Is stoneydsp::uint64 trivially copyable",
           "[type_traits][is_trivially_copyable][uint64]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint64>::value);
}

//==========================================================//is_standard_layout

TEST_CASE ("Is stoneydsp::uint8 standard-layout conforming",
           "[type_traits][is_standard_layout][uint8]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint8>::value);
}

TEST_CASE ("Is stoneydsp::uint16 standard-layout conforming",
           "[type_traits][is_standard_layout][uint16]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint16>::value);
}

TEST_CASE ("Is stoneydsp::uint32 standard-layout conforming",
           "[type_traits][is_standard_layout][uint32]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint32>::value);
}

TEST_CASE ("Is stoneydsp::uint64 standard-layout conforming",
           "[type_traits][is_standard_layout][uint64]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint64>::value);
}

//==============================================================//numeric_limits

// Ensure that your types handle their minimum and maximum values correctly.

TEST_CASE ("Numeric limits of stoneydsp::int8", "[numeric_limits][uint8]")
{
  REQUIRE (::stoneydsp::uint8{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint8>::min ());
  REQUIRE (::stoneydsp::uint8{ 255 }
           == ::std::numeric_limits< ::stoneydsp::uint8>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int16 is negative",
           "[numeric_limits][uint16]")
{
  REQUIRE (::stoneydsp::uint16{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint16>::min ());
  REQUIRE (::stoneydsp::uint16{ 65535 }
           == ::std::numeric_limits< ::stoneydsp::uint16>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int32 is negative",
           "[numeric_limits][uint32]")
{
  REQUIRE (::stoneydsp::uint32{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint32>::min ());
  REQUIRE (::stoneydsp::uint32{ 4294967295 }
           == ::std::numeric_limits< ::stoneydsp::uint32>::max ());
}

TEST_CASE ("Numeric limits of stoneydsp::int64 is negative",
           "[numeric_limits][uint64]")
{
  REQUIRE (::stoneydsp::uint64{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint64>::min ());
  REQUIRE (::stoneydsp::uint64{ 18446744073709551615ULL }
           == ::std::numeric_limits< ::stoneydsp::uint64>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::uint8", "[endianness][uint8]")
{
  ::stoneydsp::uint8 value = 0x12;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Little-endian and Big-endian will look the same for a
                      // single byte
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::uint16", "[endianness][uint16]")
{
  ::stoneydsp::uint16 value = 0x1234;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x34)
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::uint32", "[endianness][uint32]")
{
  ::stoneydsp::uint32 value = 0x12345678;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0x78)
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::uint64", "[endianness][uint64]")
{
  ::stoneydsp::uint64 value = 0x123456789ABCDEF0ULL;
  ::std::uint8_t *bytePtr = reinterpret_cast< ::std::uint8_t *> (&value);

  if (bytePtr[0] == 0xF0)
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == 0x12)
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::uint8", "[rounding][uint8]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint8 b = static_cast< ::stoneydsp::uint8> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint8
}

TEST_CASE ("Rounding behavior of stoneydsp::uint16", "[rounding][uint16]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint16 b = static_cast< ::stoneydsp::uint16> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint16
}

TEST_CASE ("Rounding behavior of stoneydsp::uint32", "[rounding][uint32]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::uint32 b = static_cast< ::stoneydsp::uint32> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint32
}

TEST_CASE ("Rounding behavior of stoneydsp::uint32", "[rounding][uint64]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::uint64 b = static_cast< ::stoneydsp::uint64> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint64
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::uint8",
           "[numeric_limits][special_values][uint8]")
{
  ::stoneydsp::uint8 min_val
      = ::std::numeric_limits< ::stoneydsp::uint8>::min ();
  ::stoneydsp::uint8 max_val
      = ::std::numeric_limits< ::stoneydsp::uint8>::max ();
  REQUIRE (min_val == 0);   // Minimum value for uint8
  REQUIRE (max_val == 255); // Maximum value for uint8
}

TEST_CASE ("Special values of stoneydsp::uint16",
           "[numeric_limits][special_values][uint16]")
{
  ::stoneydsp::uint16 min_val
      = ::std::numeric_limits< ::stoneydsp::uint16>::min ();
  ::stoneydsp::uint16 max_val
      = ::std::numeric_limits< ::stoneydsp::uint16>::max ();
  REQUIRE (min_val == 0);     // Minimum value for uint16
  REQUIRE (max_val == 65535); // Maximum value for uint16
}

TEST_CASE ("Special values of stoneydsp::uint32",
           "[numeric_limits][special_values][uint32]")
{
  ::stoneydsp::uint32 min_val
      = ::std::numeric_limits< ::stoneydsp::uint32>::min ();
  ::stoneydsp::uint32 max_val
      = ::std::numeric_limits< ::stoneydsp::uint32>::max ();
  REQUIRE (min_val == 0);          // Minimum value for uint32
  REQUIRE (max_val == 4294967295); // Maximum value for uint32
}

TEST_CASE ("Special values of stoneydsp::uint64",
           "[numeric_limits][special_values][uint64]")
{
  ::stoneydsp::uint64 min_val
      = ::std::numeric_limits< ::stoneydsp::uint64>::min ();
  ::stoneydsp::uint64 max_val
      = ::std::numeric_limits< ::stoneydsp::uint64>::max ();
  REQUIRE (min_val == 0);                       // Minimum value for uint64
  REQUIRE (max_val == 18446744073709551615ULL); // Maximum value for uint64
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint8",
           "[arithmetic][uint8]")
{
  ::stoneydsp::uint8 a = 15;
  ::stoneydsp::uint8 b = 20;
  REQUIRE (a + b == 35); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-5)); // Subtraction (wrap-around)
  REQUIRE (a * b == 300);             // Multiplication
  REQUIRE (b / a == 1);               // Division
  REQUIRE (b % a == 5);               // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::uint16",
           "[arithmetic][uint16]")
{
  ::stoneydsp::uint16 a = 1500;
  ::stoneydsp::uint16 b = 2000;
  REQUIRE (a + b == 3500); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-500)); // Subtraction (wrap-around)
  REQUIRE (a * b == 3000000);           // Multiplication
  REQUIRE (b / a == 1);                 // Division
  REQUIRE (b % a == 500);               // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::uint32",
           "[arithmetic][uint32]")
{
  ::stoneydsp::uint32 a = 15000;
  ::stoneydsp::uint32 b = 20000;
  REQUIRE (a + b == 35000); // Addition
  REQUIRE (static_cast<int> (a - b)
           == static_cast<int> (-5000)); // Subtraction (wrap-around)
  REQUIRE (a * b == 300000000);          // Multiplication
  REQUIRE (b / a == 1);                  // Division
  REQUIRE (b % a == 5000);               // Modulo
}

TEST_CASE ("Arithmetic operations with stoneydsp::uint64",
           "[arithmetic][uint64]")
{
  ::stoneydsp::uint64 a = 1500000000ULL;
  ::stoneydsp::uint64 b = 2000000000ULL;
  REQUIRE (a + b == 3500000000ULL); // Addition
  REQUIRE (
      static_cast<long long> (a - b)
      == static_cast<long long> (-500000000LL)); // Subtraction (wrap-around)
  REQUIRE (a * b == 3000000000000000000ULL);     // Multiplication
  REQUIRE (b / a == 1);                          // Division
  REQUIRE (b % a == 500000000ULL);               // Modulo
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8",
           "[serialization][uint8]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::uint8> (123);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint16",
           "[serialization][uint16]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::uint16> (12345);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint32",
           "[serialization][uint32]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::uint32> (123456789);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint64",
           "[serialization][uint64]")
{
  ::stoneydsp::test::testSerialization< ::stoneydsp::uint64> (
      1234567890123456789ULL);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint8",
           "[boundary][overflow][uint8]")
{
  ::stoneydsp::uint8 a = 255;
  ::stoneydsp::uint8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint8> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint16",
           "[boundary][overflow][uint16]")
{
  ::stoneydsp::uint16 a = 65535;
  ::stoneydsp::uint16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint16> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint32",
           "[boundary][overflow][uint32]")
{
  ::stoneydsp::uint32 a = 4294967295U;
  ::stoneydsp::uint32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint32> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

TEST_CASE ("Boundary and overflow behavior of stoneydsp::uint64",
           "[boundary][overflow][uint64]")
{
  ::stoneydsp::uint64 a = 18446744073709551615ULL;
  ::stoneydsp::uint64 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint64> (a + b)
           == 0); // Check overflow wrap-around behavior
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint8",
           "[boundary][underflow][uint8]")
{
  ::stoneydsp::uint8 a = 0;
  ::stoneydsp::uint8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint8> (a - b)
           == 255); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint16",
           "[boundary][underflow][uint16]")
{
  ::stoneydsp::uint16 a = 0;
  ::stoneydsp::uint16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint16> (a - b)
           == 65535); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint32",
           "[boundary][underflow][uint32]")
{
  ::stoneydsp::uint32 a = 0;
  ::stoneydsp::uint32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint32> (a - b)
           == 4294967295U); // Check underflow wrap-around behavior
}

TEST_CASE ("Boundary and unerflow behavior of stoneydsp::uint64",
           "[boundary][underflow][uint64]")
{
  ::stoneydsp::uint64 a = 0;
  ::stoneydsp::uint64 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint64> (a - b)
           == 18446744073709551615ULL); // Check underflow wrap-around behavior
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
