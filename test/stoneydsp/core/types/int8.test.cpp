/**
 * @file int8.test.cpp
 * @brief Test suite for stoneydsp::int8
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

TEST_CASE ("sizeof stoneydsp::int8 is 1 byte", "[sizeof][int8]")
{
  REQUIRE (sizeof (::stoneydsp::int8) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int8 is 1 byte", "[alignof][int8]")
{
  REQUIRE (alignof (::stoneydsp::int8) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_signed][int8]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int8>::value);
}

TEST_CASE ("Is stoneydsp::int8 trivially copyable",
           "[type_traits][is_trivially_copyable][int8]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int8>::value);
}

TEST_CASE ("Is stoneydsp::int8 standard-layout conforming",
           "[type_traits][is_standard_layout][int8]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int8>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::int8", "[numeric_limits][int8]")
{
  REQUIRE (::stoneydsp::int8{ -128 }
           == ::std::numeric_limits< ::stoneydsp::int8>::min ());
  REQUIRE (::stoneydsp::int8{ 127 }
           == ::std::numeric_limits< ::stoneydsp::int8>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int8", "[endianness][int8]")
{
  ::stoneydsp::int8 value = 0x12;
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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::int8", "[rounding][int8]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int8 b = static_cast< ::stoneydsp::int8> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int8
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

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int8", "[bitwise][int8]")
{
  ::stoneydsp::int8 a = 5; // 0101
  ::stoneydsp::int8 b = 3; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR:  0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int8
}

TEST_CASE ("Shift operations with stoneydsp::int8", "[bitwise][int8]")
{
  ::stoneydsp::int8 a = 5;  // 0101
  REQUIRE ((a << 1) == 10); // Left shift: 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int8", "[comparison][int8]")
{
  ::stoneydsp::int8 a = 5;
  ::stoneydsp::int8 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int8",
           "[serialization][int8]")
{
  ::std::stringstream ss;
  ::stoneydsp::int8 originalValue = 42;
  ::stoneydsp::int8 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int8",
           "[boundary][overflow][int8]")
{
  ::stoneydsp::int8 a = 127;
  ::stoneydsp::int8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int8> (a + b)
           == -128); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int8",
           "[boundary][underflow][int8]")
{
  ::stoneydsp::int8 a = -128;
  ::stoneydsp::int8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int8> (a - b)
           == 127); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int8 with standard library",
           "[compatibility][int8]")
{
  ::std::vector< ::stoneydsp::int8> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::int8>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int8 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::int8 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int8 addition", "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 12;
  ::stoneydsp::int8 b = 34;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int8 subtraction", "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 34;
  ::stoneydsp::int8 b = 12;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int8 multiplication", "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 12;
  ::stoneydsp::int8 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int8 division", "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 12;
  ::stoneydsp::int8 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int8 to int conversion",
           "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 12;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int8 to float conversion",
           "[benchmark][int8]")
{
  ::stoneydsp::int8 a = 12;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
