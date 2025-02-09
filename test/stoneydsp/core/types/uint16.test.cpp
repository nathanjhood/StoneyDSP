/**
 * @file uint16.test.cpp
 * @brief Test suite for stoneydsp::uint16
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

TEST_CASE ("sizeof stoneydsp::uint16 is 2 bytes", "[sizeof][uint16]")
{
  REQUIRE (sizeof (::stoneydsp::uint16) == 2UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint16 is 2 bytes", "[alignof][uint16]")
{
  REQUIRE (alignof (::stoneydsp::uint16) == 2UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint16]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint16>::value);
}

TEST_CASE ("Is stoneydsp::uint16 trivially copyable",
           "[type_traits][is_trivially_copyable][uint16]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint16>::value);
}

TEST_CASE ("Is stoneydsp::uint16 standard-layout conforming",
           "[type_traits][is_standard_layout][uint16]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint16>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::uint16", "[numeric_limits][uint16]")
{
  REQUIRE (::stoneydsp::uint16{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint16>::min ());
  REQUIRE (::stoneydsp::uint16{ 65535 }
           == ::std::numeric_limits< ::stoneydsp::uint16>::max ());
}

//==================================================================//endianness

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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::uint16", "[rounding][uint16]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint16 b = static_cast< ::stoneydsp::uint16> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint16
}

//==============================================================//special_values

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

//==================================================================//arithmetic

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

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint16", "[bitwise][uint16]")
{
  ::stoneydsp::uint16 a = 5; // 0000 0000 0000 0101
  ::stoneydsp::uint16 b = 3; // 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFF)
      == 65530); // NOT: 1111 1111 1111 1010 (considering uint16 wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uint16", "[bitwise][uint16]")
{
  ::stoneydsp::uint16 a = 5; // 0000 0000 0000 0101
  REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint16",
           "[comparison][uint16]")
{
  ::stoneydsp::uint16 a = 5;
  ::stoneydsp::uint16 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint16",
           "[serialization][uint16]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint16 originalValue = 42;
  ::stoneydsp::uint16 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint16",
           "[boundary][overflow][uint16]")
{
  ::stoneydsp::uint16 a = 65535;
  ::stoneydsp::uint16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint16> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint16",
           "[boundary][underflow][uint16]")
{
  ::stoneydsp::uint16 a = 0;
  ::stoneydsp::uint16 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint16> (a - b)
           == 65535); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint16 with standard library",
           "[compatibility][uint16]")
{
  ::std::vector< ::stoneydsp::uint16> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::uint16>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint16 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::uint16 (0));
  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint16 addition", "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 1200;
  ::stoneydsp::uint16 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint16 subtraction",
           "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 3400;
  ::stoneydsp::uint16 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint16 multiplication",
           "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 1200;
  ::stoneydsp::uint16 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint16 division", "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 1200;
  ::stoneydsp::uint16 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint16 to int conversion",
           "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint16 to float conversion",
           "[benchmark][uint16]")
{
  ::stoneydsp::uint16 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
