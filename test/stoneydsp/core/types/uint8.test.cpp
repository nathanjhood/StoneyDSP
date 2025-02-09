/**
 * @file uint8.test.cpp
 * @brief Test suite for stoneydsp::uint8
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
  #include <catch2/benchmark/catch_benchmark.hpp> // for `BENCHMARK`
  #include <catch2/catch_test_macros.hpp>         // for `TEST_CASE
  #include <limits>                               // for `std::numeric_limits`
  #include <numeric>                              // for `std::accumulate`
  #include <sstream>                              // for serialization tests
  #include <type_traits> // for `is_signed` and `is_unsigned`
  #include <vector>      // for compatibility tests

//======================================================================//sizeof

TEST_CASE ("sizeof stoneydsp::uint8 is 1 byte", "[sizeof][uint8]")
{
  REQUIRE (sizeof (::stoneydsp::uint8) == 1UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint8 is 1 byte", "[alignof][uint8]")
{
  REQUIRE (alignof (::stoneydsp::uint8) == 1UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint8]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint8>::value);
}

TEST_CASE ("Is stoneydsp::uint8 trivially copyable",
           "[type_traits][is_trivially_copyable][uint8]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint8>::value);
}

TEST_CASE ("Is stoneydsp::uint8 standard-layout conforming",
           "[type_traits][is_standard_layout][uint8]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint8>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::uint8", "[numeric_limits][uint8]")
{
  REQUIRE (::stoneydsp::uint8{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint8>::min ());
  REQUIRE (::stoneydsp::uint8{ 255 }
           == ::std::numeric_limits< ::stoneydsp::uint8>::max ());
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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::uint8", "[rounding][uint8]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint8 b = static_cast< ::stoneydsp::uint8> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint8
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
//=====================================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint8", "[bitwise][uint8]")
{
  ::stoneydsp::uint8 a = 5; // 0101
  ::stoneydsp::uint8 b = 3; // 0011

  REQUIRE ((a & b) == 1); // AND: 0001
  REQUIRE ((a | b) == 7); // OR: 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0110
  REQUIRE ((~a & 0xFF)
           == 250); // NOT: 1111_1010 (considering uint8 wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uint8", "[bitwise][uint8]")
{
  ::stoneydsp::uint8 a = 5; // 0101
  REQUIRE ((a << 1) == 10); // Left shift: 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0010
}

//==================================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint8",
           "[comparison][uint8]")
{
  ::stoneydsp::uint8 a = 5;
  ::stoneydsp::uint8 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8",
           "[serialization][uint8]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint8 originalValue = 42;
  ::stoneydsp::uint8 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
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

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint8",
           "[boundary][underflow][uint8]")
{
  ::stoneydsp::uint8 a = 0;
  ::stoneydsp::uint8 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint8> (a - b)
           == 255); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint8 with standard library",
           "[compatibility][uint8]")
{
  ::std::vector< ::stoneydsp::uint8> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::uint8>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint8 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::uint8 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint8 addition", "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 12;
  ::stoneydsp::uint8 b = 34;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint8 subtraction", "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 34;
  ::stoneydsp::uint8 b = 12;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint8 multiplication",
           "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 12;
  ::stoneydsp::uint8 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint8 division", "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 12;
  ::stoneydsp::uint8 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint8 to int conversion",
           "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 12;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint8 to float conversion",
           "[benchmark][uint8]")
{
  ::stoneydsp::uint8 a = 12;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
