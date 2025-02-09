/**
 * @file uint32.test.cpp
 * @brief Test suite for stoneydsp::uint32
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

TEST_CASE ("sizeof stoneydsp::uint32 is 4 bytes", "[sizeof][uint32]")
{
  REQUIRE (sizeof (::stoneydsp::uint32) == 4UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint32 is 4 bytes", "[alignof][uint32]")
{
  REQUIRE (alignof (::stoneydsp::uint32) == 4UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint32]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint32>::value);
}

TEST_CASE ("Is stoneydsp::uint32 trivially copyable",
           "[type_traits][is_trivially_copyable][uint32]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint32>::value);
}

TEST_CASE ("Is stoneydsp::uint32 standard-layout conforming",
           "[type_traits][is_standard_layout][uint32]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint32>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::uint32", "[numeric_limits][uint32]")
{
  REQUIRE (::stoneydsp::uint32{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint32>::min ());
  REQUIRE (::stoneydsp::uint32{ 4294967295UL }
           == ::std::numeric_limits< ::stoneydsp::uint32>::max ());
}

//==================================================================//endianness

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

//====================================================================//rounding

TEST_CASE ("Rounding behavior of stoneydsp::uint32", "[rounding][uint32]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint32 b = static_cast< ::stoneydsp::uint32> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint32
}

//==============================================================//special_values

TEST_CASE ("Special values of stoneydsp::uint32",
           "[numeric_limits][special_values][uint32]")
{
  ::stoneydsp::uint32 min_val
      = ::std::numeric_limits< ::stoneydsp::uint32>::min ();
  ::stoneydsp::uint32 max_val
      = ::std::numeric_limits< ::stoneydsp::uint32>::max ();
  REQUIRE (min_val == 0);            // Minimum value for uint32
  REQUIRE (max_val == 4294967295UL); // Maximum value for uint32
}

//==================================================================//arithmetic

TEST_CASE ("Arithmetic operations with stoneydsp::uint32",
           "[arithmetic][uint32]")
{
  ::stoneydsp::uint32 a = 1500000000UL;
  ::stoneydsp::uint32 b = 2UL;
  REQUIRE (a + b == 1500000002UL); // Addition
  REQUIRE (a - b == 1499999998UL); // Subtraction
  REQUIRE (a * b == 3000000000UL); // Multiplication
  REQUIRE (b / a == 0);            // Division
  REQUIRE (b % a == 2UL);          // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint32", "[bitwise][uint32]")
{
  ::stoneydsp::uint32 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint32 b = 3; // 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE ((~a & 0xFFFFFFFF)
           == 4294967290UL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1010
                             // (considering uint32 wrap-around)
}

TEST_CASE ("Shift operations with stoneydsp::uint32", "[bitwise][uint32]")
{
  ::stoneydsp::uint32 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0101
  REQUIRE ((a << 1)
           == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1)
           == 2); // Right shift: 0000 0000 0000 0000 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint32",
           "[comparison][uint32]")
{
  ::stoneydsp::uint32 a = 5;
  ::stoneydsp::uint32 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint32",
           "[serialization][uint32]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint32 originalValue = 42;
  ::stoneydsp::uint32 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint32",
           "[boundary][overflow][uint32]")
{
  ::stoneydsp::uint32 a = 4294967295UL;
  ::stoneydsp::uint32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint32> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint32",
           "[boundary][underflow][uint32]")
{
  ::stoneydsp::uint32 a = 0;
  ::stoneydsp::uint32 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint32> (a - b)
           == 4294967295UL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint32 with standard library",
           "[compatibility][uint32]")
{
  ::std::vector< ::stoneydsp::uint32> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::uint32>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint32 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::uint32 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint32 addition", "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 1200;
  ::stoneydsp::uint32 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint32 subtraction",
           "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 3400;
  ::stoneydsp::uint32 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint32 multiplication",
           "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 1200;
  ::stoneydsp::uint32 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint32 division", "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 1200;
  ::stoneydsp::uint32 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint32 to int conversion",
           "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint32 to float conversion",
           "[benchmark][uint32]")
{
  ::stoneydsp::uint32 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
