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

  #include <limits>      // for `std::numeric_limits`
  #include <sstream>     // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`

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
// [serialization]

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

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int8",
           "[serialization][int8]")
{
  ::std::stringstream ss;
  ::stoneydsp::int8 originalValue = -123;
  ::stoneydsp::int8 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int16",
           "[serialization][int16]")
{
  ::std::stringstream ss;
  ::stoneydsp::int16 originalValue = -12345;
  ::stoneydsp::int16 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int32",
           "[serialization][int32]")
{
  ::std::stringstream ss;
  ::stoneydsp::int32 originalValue = -123456789;
  ::stoneydsp::int32 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::int64",
           "[serialization][int64]")
{
  ::std::stringstream ss;
  ::stoneydsp::int64 originalValue = -1234567890123456789LL;
  ::stoneydsp::int64 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//======================================================================//sizeof

// Ensure types have the expected size across different architectures.

TEST_CASE ("sizeof stoneydsp::uint8 is 1 byte", "[sizeof][uint8]")
{
  REQUIRE (sizeof (::stoneydsp::uint8) == (unsigned long)1UL);
}

TEST_CASE ("sizeof stoneydsp::uint16 is 2 bytes", "[sizeof][uint16]")
{
  REQUIRE (sizeof (::stoneydsp::uint16) == (unsigned long)2UL);
}

TEST_CASE ("sizeof stoneydsp::uint32 is 4 bytes", "[sizeof][uint32]")
{
  REQUIRE (sizeof (::stoneydsp::uint32) == (unsigned long)4UL);
}

TEST_CASE ("sizeof stoneydsp::uint64 is 8 bytes", "[sizeof][uint64]")
{
  REQUIRE (sizeof (::stoneydsp::uint64) == (unsigned long)8UL);
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

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8",
           "[serialization][uint8]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint8 originalValue = 123;
  ::stoneydsp::uint8 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint16",
           "[serialization][uint16]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint16 originalValue = 12345;
  ::stoneydsp::uint16 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint32",
           "[serialization][uint32]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint32 originalValue = 123456789;
  ::stoneydsp::uint32 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint64",
           "[serialization][uint64]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint64 originalValue = 1234567890123456789ULL;
  ::stoneydsp::uint64 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
