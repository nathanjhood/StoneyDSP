/**
 * @file uint64.test.cpp
 * @brief Test suite for stoneydsp::uint64
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

TEST_CASE ("sizeof stoneydsp::uint64 is 8 bytes", "[sizeof][uint64]")
{
  REQUIRE (sizeof (::stoneydsp::uint64) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::uint64 is 8 bytes", "[alignof][uint64]")
{
  REQUIRE (alignof (::stoneydsp::uint64) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_unsigned][uint64]")
{
  REQUIRE (::std::is_unsigned< ::stoneydsp::uint64>::value);
}

TEST_CASE ("Is stoneydsp::uint64 trivially copyable",
           "[type_traits][is_trivially_copyable][uint64]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::uint64>::value);
}

TEST_CASE ("Is stoneydsp::uint64 standard-layout conforming",
           "[type_traits][is_standard_layout][uint64]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::uint64>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::uint64", "[numeric_limits][uint64]")
{
  REQUIRE (::stoneydsp::uint64{ 0 }
           == ::std::numeric_limits< ::stoneydsp::uint64>::min ());
  REQUIRE (::stoneydsp::uint64{ 18446744073709551615ULL }
           == ::std::numeric_limits< ::stoneydsp::uint64>::max ());
}

//==================================================================//endianness

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

TEST_CASE ("Rounding behavior of stoneydsp::uint64", "[rounding][uint64]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::uint64 b = static_cast< ::stoneydsp::uint64> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to uint64
}

//==============================================================//special_values

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

TEST_CASE ("Arithmetic operations with stoneydsp::uint64",
           "[arithmetic][uint64]")
{
  ::stoneydsp::uint64 a = 1500000000000000000ULL;
  ::stoneydsp::uint64 b = 2ULL;
  REQUIRE (a + b == 1500000000000000002ULL); // Addition
  REQUIRE (a - b == 1499999999999999998ULL); // Subtraction
  REQUIRE (a * b == 3000000000000000000ULL); // Multiplication
  REQUIRE (b / a == 0);                      // Division
  REQUIRE (b % a == 2ULL);                   // Modulo
}

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::uint64", "[bitwise][uint64]")
{
  // clang-format off
  ::stoneydsp::uint64 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::uint64 b = 3; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (
      (~a & 0xFFFFFFFFFFFFFFFFULL)
      == 18446744073709551610ULL); // NOT: 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1010 (considering uint64 wrap-around)
	// clang-format off
}

TEST_CASE ("Shift operations with stoneydsp::uint64", "[bitwise][uint64]")
{
	// clang-format off
  ::stoneydsp::uint64 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0101
  REQUIRE ((a << 1) == 10);  // Left shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);   // Right shift: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010
  // clang-format on
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::uint64",
           "[comparison][uint64]")
{
  ::stoneydsp::uint64 a = 5;
  ::stoneydsp::uint64 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::uint64",
           "[serialization][uint64]")
{
  ::std::stringstream ss;
  ::stoneydsp::uint64 originalValue = 42;
  ::stoneydsp::uint64 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::uint64",
           "[boundary][overflow][uint64]")
{
  ::stoneydsp::uint64 a = 18446744073709551615ULL;
  ::stoneydsp::uint64 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint64> (a + b)
           == 0); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::uint64",
           "[boundary][underflow][uint64]")
{
  ::stoneydsp::uint64 a = 0;
  ::stoneydsp::uint64 b = 1;
  REQUIRE (static_cast< ::stoneydsp::uint64> (a - b)
           == 18446744073709551615ULL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::uint64 with standard library",
           "[compatibility][uint64]")
{
  ::std::vector< ::stoneydsp::uint64> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::uint64>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::uint64 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::uint64 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::uint64 addition", "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 1200;
  ::stoneydsp::uint64 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::uint64 subtraction",
           "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 3400;
  ::stoneydsp::uint64 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::uint64 multiplication",
           "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 1200;
  ::stoneydsp::uint64 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::uint64 division", "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 1200;
  ::stoneydsp::uint64 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::uint64 to int conversion",
           "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::uint64 to float conversion",
           "[benchmark][uint64]")
{
  ::stoneydsp::uint64 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
