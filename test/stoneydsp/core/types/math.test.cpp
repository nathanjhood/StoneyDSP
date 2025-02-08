/**
 * @file math.test.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/math.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST)

//==============================================================================

  #include <catch2/catch_test_macros.hpp>
  #include <catch2/matchers/catch_matchers_floating_point.hpp>
//==============================================================================

  #include "stoneydsp/core/types/int.h"

//==============================================================================

  #include <cmath>
  #include <cstring>
  #include <limits> // for `std::numeric_limits`
  #include <sstream>
  #include <type_traits> // for `is_signed`

//==============================================================================

// Test tags provided by this file:
//
// [float_t]
// [double_t]
//
// [sizeof]
// [alignof]
//
// [type_traits]
// [is_signed]
// [is_trivially_copyable]
// [is_standard_layout]
//
// [precision]
// [rounding]
// [special_values]
// [arithmetic]
// [conversion]
// [endianness]
// [serialization]
// [boundary]
// [underflow]
// [overflow]

//======================================================================//sizeof

// Ensure types have the expected size across different architectures.

TEST_CASE ("sizeof stoneydsp::double_t is 8 bytes", "[sizeof][double_t]")
{
  REQUIRE (sizeof (::stoneydsp::double_t) == (unsigned long)8UL);
}

TEST_CASE ("sizeof stoneydsp::float_t is 8 bytes", "[sizeof][float_t]")
{
  REQUIRE (sizeof (::stoneydsp::float_t) == (unsigned long)4UL);
}

//=====================================================================//alignof

// Ensure types have the expected alignment across different architectures.

TEST_CASE ("alignof stoneydsp::double_t is 8 bytes", "[alignof][double_t]")
{
  REQUIRE (alignof (::stoneydsp::double_t) == (unsigned long)8UL);
}

TEST_CASE ("alignof stoneydsp::float_t is 4 bytes", "[alignof][float_t]")
{
  REQUIRE (alignof (::stoneydsp::float_t) == (unsigned long)4UL);
}

//=================================================================//type_traits

// Ensure types have the expected signedness across different architectures.

TEST_CASE ("Signed-ness of stoneydsp::double_t is positive",
           "[type_traits][is_signed][double_t]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::double_t>::value);
}

TEST_CASE ("Signed-ness of stoneydsp::float_t is positive",
           "[type_traits][is_signed][float_t]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::float_t>::value);
}

//=======================================================//is_trivially_copyable

TEST_CASE ("Is stoneydsp::double_t trivially copyable",
           "[type_traits][is_trivially_copyable][double_t]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::double_t>::value);
}

TEST_CASE ("Is stoneydsp::float_t trivially copyable",
           "[type_traits][is_trivially_copyable][float_t]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::float_t>::value);
}

//==========================================================//is_standard_layout

TEST_CASE ("Is stoneydsp::double_t standard-layout conforming",
           "[type_traits][is_standard_layout][double_t]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::double_t>::value);
}

TEST_CASE ("Is stoneydsp::float_t standard-layout conforming",
           "[type_traits][is_standard_layout][float_t]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::float_t>::value);
}

//==============================================================//numeric_limits

// Ensure that your types handle their minimum and maximum values correctly.

TEST_CASE ("Numeric limits of stoneydsp::double_t",
           "[numeric_limits][double_t]")
{
  REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::min ()
           == 2.2250738585072014e-308);
  REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::max ()
           == 1.7976931348623158e+308);
  REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::epsilon ()
           == 2.2204460492503131e-16);
  REQUIRE (::std::numeric_limits< ::stoneydsp::double_t>::lowest ()
           == -1.7976931348623158e+308);
}

TEST_CASE ("Numeric limits of stoneydsp::float_t", "[numeric_limits][float_t]")
{
  REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::min ()
           == 1.175494351e-38F);
  REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::max ()
           == 3.402823466e+38F);
  REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::epsilon ()
           == 1.192092896e-07F);
  REQUIRE (::std::numeric_limits< ::stoneydsp::float_t>::lowest ()
           == -3.402823466e+38F);
}

//===================================================================//precision

TEST_CASE ("Precision and comparison of stoneydsp::double_t",
           "[precision][double_t]")
{
  ::stoneydsp::double_t a = 0.1;
  ::stoneydsp::double_t b = 0.1;
  REQUIRE_THAT (a, ::Catch::Matchers::WithinRel (b, 1e-12));
}

TEST_CASE ("Precision and comparison of stoneydsp::float_t",
           "[precision][float_t]")
{
  ::stoneydsp::float_t a = 0.1f;
  ::stoneydsp::float_t b = 0.1f;
  REQUIRE_THAT (a, ::Catch::Matchers::WithinRel (b, 1e-6f));
}

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::double_t", "[rounding][double_t]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::double_t b = ::std::round (a);
  REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (2.0, 1e-12));
}

TEST_CASE ("Rounding behavior of stoneydsp::float_t", "[rounding][float_t]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::float_t b = ::std::round (a);
  REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (2.0f, 1e-6f));
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::double_t",
           "[numeric_limits][special_values][double_t]")
{
  ::stoneydsp::double_t nan
      = ::std::numeric_limits< ::stoneydsp::double_t>::quiet_NaN ();
  ::stoneydsp::double_t inf
      = ::std::numeric_limits< ::stoneydsp::double_t>::infinity ();
  REQUIRE (::std::isnan (nan));
  REQUIRE (::std::isinf (inf));
}

TEST_CASE ("Special values of stoneydsp::float_t",
           "[numeric_limits][special_values][float_t]")
{
  ::stoneydsp::float_t nan
      = ::std::numeric_limits< ::stoneydsp::float_t>::quiet_NaN ();
  ::stoneydsp::float_t inf
      = ::std::numeric_limits< ::stoneydsp::float_t>::infinity ();
  REQUIRE (::std::isnan (nan));
  REQUIRE (::std::isinf (inf));
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::double_t",
           "[arithmetic][double_t]")
{
  ::stoneydsp::double_t a = 1.5;
  ::stoneydsp::double_t b = 2.0;
  REQUIRE_THAT (a + b, ::Catch::Matchers::WithinRel (3.5, 1e-12));
  REQUIRE_THAT (a - b, ::Catch::Matchers::WithinRel (-0.5, 1e-12));
  REQUIRE_THAT (a * b, ::Catch::Matchers::WithinRel (3.0, 1e-12));
  REQUIRE_THAT (a / b, ::Catch::Matchers::WithinRel (0.75, 1e-12));
}

TEST_CASE ("Arithmetic operations with stoneydsp::float_t",
           "[arithmetic][float_t]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::float_t b = 2.0f;
  REQUIRE_THAT (a + b, ::Catch::Matchers::WithinRel (3.5f, 1e-6f));
  REQUIRE_THAT (a - b, ::Catch::Matchers::WithinRel (-0.5f, 1e-6f));
  REQUIRE_THAT (a * b, ::Catch::Matchers::WithinRel (3.0f, 1e-6f));
  REQUIRE_THAT (a / b, ::Catch::Matchers::WithinRel (0.75f, 1e-6f));
}

//==================================================================//conversion

TEST_CASE ("Conversion from stoneydsp::double_t to stoneydsp::float_t",
           "[conversion][double_t][float_t]")
{
  ::stoneydsp::double_t a = 0.1;
  ::stoneydsp::float_t b = static_cast< ::stoneydsp::float_t> (a);
  REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (0.1f, 1e-6f));
}

TEST_CASE ("Conversion from stoneydsp::float_t to stoneydsp::double_t",
           "[conversion][float_t][double_t]")
{
  ::stoneydsp::float_t a = 0.1f;
  ::stoneydsp::double_t b = static_cast< ::stoneydsp::double_t> (a);
  REQUIRE_THAT (b, ::Catch::Matchers::WithinRel (0.1, 1e-6));
}

//===============================================================//serialization

TEST_CASE ("Serialization and deserialization for stoneydsp::float_t",
           "[serialization][float_t]")
{
  ::std::stringstream ss;
  ::stoneydsp::float_t originalValue = 123.456f;
  ::stoneydsp::float_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE_THAT (originalValue,
                ::Catch::Matchers::WithinRel (deserializedValue, 1e-6f));
}

TEST_CASE ("Serialization and deserialization for stoneydsp::double_t",
           "[serialization][double_t]")
{
  ::std::stringstream ss;
  ::stoneydsp::double_t originalValue = 123.456789;
  ::stoneydsp::double_t deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE_THAT (originalValue,
                ::Catch::Matchers::WithinRel (deserializedValue, 1e-12));
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::double_t with arbitrary value",
           "[endianness][double_t][arbitrary_value]")
{
  ::stoneydsp::double_t value = 123.456;
  ::stoneydsp::uint8 *bytePtr
      = reinterpret_cast< ::stoneydsp::uint8 *> (&value);

  if (bytePtr[0]
      == reinterpret_cast< ::stoneydsp::uint8 *> (
          &value)[sizeof (::stoneydsp::double_t) - 1])
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == reinterpret_cast< ::stoneydsp::uint8 *> (&value)[0])
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

TEST_CASE ("Endianness handling for stoneydsp::double_t with specific value",
           "[endianness][double_t][specific_value]")
{
  ::stoneydsp::double_t value = 1.0;
  unsigned char bytes[sizeof (::stoneydsp::double_t)];
  std::memcpy (bytes, &value, sizeof (value));

  if (bytes[0] == 0x3f && bytes[1] == 0xf0 && bytes[2] == 0x00
      && bytes[3] == 0x00 && bytes[4] == 0x00 && bytes[5] == 0x00
      && bytes[6] == 0x00 && bytes[7] == 0x00)
    {
      // Little-endian representation of 1.0
      REQUIRE (true);
    }
  else if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0x00
           && bytes[3] == 0x00 && bytes[4] == 0x00 && bytes[5] == 0x00
           && bytes[6] == 0xf0 && bytes[7] == 0x3f)
    {
      // Big-endian representation of 1.0
      REQUIRE (true);
    }
  else
    {
      REQUIRE (false); // Unexpected endianness
    }
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::float_t with arbitrary value",
           "[endianness][float_t][arbitrary_value]")
{
  ::stoneydsp::float_t value = 123.456f;
  ::stoneydsp::uint8 *bytePtr
      = reinterpret_cast< ::stoneydsp::uint8 *> (&value);

  if (bytePtr[0]
      == reinterpret_cast< ::stoneydsp::uint8 *> (
          &value)[sizeof (::stoneydsp::float_t) - 1])
    {
      REQUIRE (true); // Little-endian
    }
  else if (bytePtr[0] == reinterpret_cast< ::stoneydsp::uint8 *> (&value)[0])
    {
      REQUIRE (true); // Big-endian
    }
  else
    {
      REQUIRE (false); // Unknown endianness
    }
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::float_t with specific value",
           "[endianness][float_t][specific_value]")
{
  ::stoneydsp::float_t value = 1.0f;
  unsigned char bytes[sizeof (::stoneydsp::float_t)];
  std::memcpy (bytes, &value, sizeof (value));

  if (bytes[0] == 0x3f && bytes[1] == 0x80 && bytes[2] == 0x00
      && bytes[3] == 0x00)
    {
      // Little-endian representation of 1.0f
      REQUIRE (true);
    }
  else if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0x80
           && bytes[3] == 0x3f)
    {
      // Big-endian representation of 1.0f
      REQUIRE (true);
    }
  else
    {
      REQUIRE (false); // Unexpected endianness
    }
}

//====================================================================//boundary

TEST_CASE ("Boundary value handling for stoneydsp::double_t",
           "[boundary][double_t]")
{
  ::stoneydsp::double_t max_val
      = std::numeric_limits< ::stoneydsp::double_t>::max ();
  ::stoneydsp::double_t min_val
      = std::numeric_limits< ::stoneydsp::double_t>::min ();
  REQUIRE (std::isfinite (max_val));
  REQUIRE (std::isfinite (min_val));
}

TEST_CASE ("Boundary value handling for stoneydsp::float_t",
           "[boundary][float_t]")
{
  ::stoneydsp::float_t max_val
      = std::numeric_limits< ::stoneydsp::float_t>::max ();
  ::stoneydsp::float_t min_val
      = std::numeric_limits< ::stoneydsp::float_t>::min ();
  REQUIRE (std::isfinite (max_val));
  REQUIRE (std::isfinite (min_val));
}

//====================================================================//overflow

TEST_CASE ("Overflow behavior for stoneydsp::double_t", "[overflow][double_t]")
{
  ::stoneydsp::double_t max_val
      = std::numeric_limits< ::stoneydsp::double_t>::max ();
  ::stoneydsp::double_t overflow_val = max_val * 2.0;
  REQUIRE (std::isinf (overflow_val)); // Check for positive overflow
}

TEST_CASE ("Overflow behavior for stoneydsp::float_t", "[overflow][float_t]")
{
  ::stoneydsp::float_t max_val
      = std::numeric_limits< ::stoneydsp::float_t>::max ();
  ::stoneydsp::float_t overflow_val = max_val * 2.0f;
  REQUIRE (std::isinf (overflow_val)); // Check for positive overflow
}

//===================================================================//underflow

TEST_CASE ("Underflow behavior for stoneydsp::double_t",
           "[underflow][boundary][double_t]")
{
  ::stoneydsp::double_t min_val
      = std::numeric_limits< ::stoneydsp::double_t>::min ();
  ::stoneydsp::double_t underflow_val = min_val / 2.0;
  REQUIRE (underflow_val == 0.0); // Check for underflow to zero
}

TEST_CASE ("Underflow behavior for stoneydsp::float_t",
           "[underflow][boundary][float_t]")
{
  ::stoneydsp::float_t min_val
      = std::numeric_limits< ::stoneydsp::float_t>::min ();
  ::stoneydsp::float_t underflow_val = min_val / 2.0f;
  REQUIRE (underflow_val == 0.0f); // Check for underflow to zero
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
