/**
 * @file int16.test.cpp
 * @brief Test suite for stoneydsp::int16
 * @copyright Copyright (c) 2025
 *
 */

//==============================================================================

#include "stoneydsp/core/types/int.h"

//==============================================================================

#if defined(STONEYDSP_BUILD_TEST)

//==============================================================================

  #include "stoneydsp/core/system/compiler.h" // for `STONEYDSP_PUBLIC_FUNCTION`
  #include "stoneydsp/core/types/math.h"      // for `stoneydsp::float_t`
  #include <algorithm>                        // for `std::sort`
  #include <catch2/benchmark/catch_benchmark.hpp>
  #include <catch2/catch_test_macros.hpp>
  #include <limits>      // for `std::numeric_limits`
  #include <numeric>     // for `std::accumulate`
  #include <sstream>     // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::int16 is 2 bytes", "[sizeof][int16]")
{
  REQUIRE (sizeof (::stoneydsp::int16) == 2UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int16 is 2 bytes", "[alignof][int16]")
{
  REQUIRE (alignof (::stoneydsp::int16) == 2UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_signed][int16]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int16>::value);
}

TEST_CASE ("Is stoneydsp::int16 trivially copyable",
           "[type_traits][is_trivially_copyable][int16]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int16>::value);
}

TEST_CASE ("Is stoneydsp::int16 standard-layout conforming",
           "[type_traits][is_standard_layout][int16]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int16>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::int16", "[numeric_limits][int16]")
{
  REQUIRE (::stoneydsp::int16{ -32768 }
           == ::std::numeric_limits< ::stoneydsp::int16>::min ());
  REQUIRE (::stoneydsp::int16{ 32767 }
           == ::std::numeric_limits< ::stoneydsp::int16>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int16", "[endianness][int16]")
{
  ::stoneydsp::int16 value = 0x1234;
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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::int16", "[rounding][int16]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int16 b = static_cast< ::stoneydsp::int16> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int16
}

//==============================================================//special_values

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

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::int16",
           "[arithmetic][int16]")
{
  ::stoneydsp::int16 a = 15000;
  ::stoneydsp::int16 b = 20000;
  REQUIRE (a + b == 35000);     // Addition
  REQUIRE (a - b == -5000);     // Subtraction
  REQUIRE (a * b == 300000000); // Multiplication
  REQUIRE (b / a == 1);         // Division
  REQUIRE (b % a == 5000);      // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int16", "[bitwise][int16]")
{
  ::stoneydsp::int16 a = 5; // 0000 0000 0000 0101
  ::stoneydsp::int16 b = 3; // 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int16
}

TEST_CASE ("Shift operations with stoneydsp::int16", "[bitwise][int16]")
{
  ::stoneydsp::int16 a = 5; // 0000 0000 0000 0101
  REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int16",
           "[comparison][int16]")
{
  ::stoneydsp::int16 a = 5;
  ::stoneydsp::int16 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int16",
           "[serialization][int16]")
{
  ::std::stringstream ss;
  ::stoneydsp::int16 originalValue = 42;
  ::stoneydsp::int16 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int16",
           "[boundary][overflow][int16]")
{
  ::stoneydsp::int16 a = 32767;
  ::stoneydsp::int16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int16> (a + b)
           == -32768); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int16",
           "[boundary][underflow][int16]")
{
  ::stoneydsp::int16 a = -32768;
  ::stoneydsp::int16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int16> (a - b)
           == 32767); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int16 with standard library",
           "[compatibility][int16]")
{
  ::std::vector< ::stoneydsp::int16> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::int16>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int16 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::int16 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int16 addition", "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 1200;
  ::stoneydsp::int16 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int16 subtraction", "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 3400;
  ::stoneydsp::int16 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int16 multiplication",
           "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 1200;
  ::stoneydsp::int16 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int16 division", "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 1200;
  ::stoneydsp::int16 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int16 to int conversion",
           "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int16 to float conversion",
           "[benchmark][int16]")
{
  ::stoneydsp::int16 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
