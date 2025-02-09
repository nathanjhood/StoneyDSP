/**
 * @file int32.test.cpp
 * @brief Test suite for stoneydsp::int32
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

TEST_CASE ("sizeof stoneydsp::int32 is 4 bytes", "[sizeof][int32]")
{
  REQUIRE (sizeof (::stoneydsp::int32) == 4UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int32 is 4 bytes", "[alignof][int32]")
{
  REQUIRE (alignof (::stoneydsp::int32) == 4UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_signed][int32]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int32>::value);
}

TEST_CASE ("Is stoneydsp::int32 trivially copyable",
           "[type_traits][is_trivially_copyable][int32]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int32>::value);
}

TEST_CASE ("Is stoneydsp::int32 standard-layout conforming",
           "[type_traits][is_standard_layout][int32]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int32>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::int32", "[numeric_limits][int32]")
{
  REQUIRE (::stoneydsp::int32{ -2147483648 }
           == ::std::numeric_limits< ::stoneydsp::int32>::min ());
  REQUIRE (::stoneydsp::int32{ 2147483647 }
           == ::std::numeric_limits< ::stoneydsp::int32>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int32", "[endianness][int32]")
{
  ::stoneydsp::int32 value = 0x12345678;
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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::int32", "[rounding][int32]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int32 b = static_cast< ::stoneydsp::int32> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int32
}

//==============================================================//special_values

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

//==================================================================//arithmetic

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

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int32", "[bitwise][int32]")
{
  ::stoneydsp::int32 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int32 b = 3; // 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int32
}

TEST_CASE ("Shift operations with stoneydsp::int32", "[bitwise][int32]")
{
  ::stoneydsp::int32 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0101
  REQUIRE ((a << 1)
           == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1)
           == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int32",
           "[comparison][int32]")
{
  ::stoneydsp::int32 a = 5;
  ::stoneydsp::int32 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int32",
           "[serialization][int32]")
{
  ::std::stringstream ss;
  ::stoneydsp::int32 originalValue = 42;
  ::stoneydsp::int32 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int32",
           "[boundary][overflow][int32]")
{
  ::stoneydsp::int32 a = 2147483647;
  ::stoneydsp::int32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int32> (a + b)
           == -2147483648); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int32",
           "[boundary][underflow][int32]")
{
  ::stoneydsp::int32 a = -2147483648;
  ::stoneydsp::int32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int32> (a - b)
           == 2147483647); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int32 with standard library",
           "[compatibility][int32]")
{
  ::std::vector< ::stoneydsp::int32> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::int32>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int32 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::int32 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int32 addition", "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 1200;
  ::stoneydsp::int32 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int32 subtraction", "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 3400;
  ::stoneydsp::int32 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int32 multiplication",
           "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 1200;
  ::stoneydsp::int32 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int32 division", "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 1200;
  ::stoneydsp::int32 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int32 to int conversion",
           "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int32 to float conversion",
           "[benchmark][int32]")
{
  ::stoneydsp::int32 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
