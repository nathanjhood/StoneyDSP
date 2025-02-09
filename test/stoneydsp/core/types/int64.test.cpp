/**
 * @file int64.test.cpp
 * @brief Test suite for stoneydsp::int64
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

TEST_CASE ("sizeof stoneydsp::int64 is 8 bytes", "[sizeof][int64]")
{
  REQUIRE (sizeof (::stoneydsp::int64) == 8UL);
}

//=====================================================================//alignof

TEST_CASE ("alignof stoneydsp::int64 is 8 bytes", "[alignof][int64]")
{
  REQUIRE (alignof (::stoneydsp::int64) == 8UL);
}

//=================================================================//type_traits

TEST_CASE ("Check if types are signed or unsigned",
           "[type_traits][is_signed][int64]")
{
  REQUIRE (::std::is_signed< ::stoneydsp::int64>::value);
}

TEST_CASE ("Is stoneydsp::int64 trivially copyable",
           "[type_traits][is_trivially_copyable][int64]")
{
  REQUIRE (::std::is_trivially_copyable< ::stoneydsp::int64>::value);
}

TEST_CASE ("Is stoneydsp::int64 standard-layout conforming",
           "[type_traits][is_standard_layout][int64]")
{
  REQUIRE (::std::is_standard_layout< ::stoneydsp::int64>::value);
}

//==============================================================//numeric_limits

TEST_CASE ("Numeric limits of stoneydsp::int64", "[numeric_limits][int64]")
{
  REQUIRE (::stoneydsp::int64{ -9223372036854775807LL - 1 }
           == ::std::numeric_limits< ::stoneydsp::int64>::min ());
  REQUIRE (::stoneydsp::int64{ 9223372036854775807LL }
           == ::std::numeric_limits< ::stoneydsp::int64>::max ());
}

//==================================================================//endianness

TEST_CASE ("Endianness handling for stoneydsp::int64", "[endianness][int64]")
{
  ::stoneydsp::int64 value = 0x123456789ABCDEF0LL;
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

TEST_CASE ("Rounding behavior of stoneydsp::int64", "[rounding][int64]")
{
  ::stoneydsp::float_t a = 1.5f;
  ::stoneydsp::int64 b = static_cast< ::stoneydsp::int64> (::std::round (a));
  REQUIRE (b == 2); // 1.5 rounded to nearest integer and cast to int64
}

//==============================================================//special_values

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

//===============================================================//bitwise

TEST_CASE ("Bitwise operations with stoneydsp::int64", "[bitwise][int64]")
{
  ::stoneydsp::int64 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0000 0000
                            // 0000 0000 0000 0000 0000 0000 0101
  ::stoneydsp::int64 b = 3; // 0000 0000 0000 0000 0000 0000 0000 0000 0000
                            // 0000 0000 0000 0000 0000 0000 0011

  REQUIRE ((a & b) == 1); // AND: 0000 0000 0000 0000 0000 0000 0000 0000 0000
                          // 0000 0000 0000 0000 0000 0000 0001
  REQUIRE ((a | b) == 7); // OR:  0000 0000 0000 0000 0000 0000 0000 0000 0000
                          // 0000 0000 0000 0000 0000 0000 0111
  REQUIRE ((a ^ b) == 6); // XOR: 0000 0000 0000 0000 0000 0000 0000 0000 0000
                          // 0000 0000 0000 0000 0000 0000 0110
  REQUIRE (~a == -6);     // NOT: considering wrap-around for int64
}

TEST_CASE ("Shift operations with stoneydsp::int64", "[bitwise][int64]")
{
  ::stoneydsp::int64 a = 5; // 0000 0000 0000 0000 0000 0000 0000 0000 0000
                            // 0000 0000 0000 0000 0000 0000 0101
  REQUIRE ((a << 1) == 10); // Left shift: 0000 0000 0000 0000 0000 0000 0000
                            // 0000 0000 0000 0000 0000 0000 0000 0000 1010
  REQUIRE ((a >> 1) == 2);  // Right shift: 0000 0000 0000 0000 0000 0000 0000
                            // 0000 0000 0000 0000 0000 0000 0000 0000 0010
}

//===============================================================//comparison

TEST_CASE ("Comparison operations with stoneydsp::int64",
           "[comparison][int64]")
{
  ::stoneydsp::int64 a = 5;
  ::stoneydsp::int64 b = 3;
  REQUIRE ((a == b) == false);
  REQUIRE ((a != b) == true);
  REQUIRE ((a > b) == true);
  REQUIRE ((a < b) == false);
  REQUIRE ((a >= b) == true);
  REQUIRE ((a <= b) == false);
}

//===============================================================//serialization

TEST_CASE ("Check serialization and deserialization for stoneydsp::int64",
           "[serialization][int64]")
{
  ::std::stringstream ss;
  ::stoneydsp::int64 originalValue = 42;
  ::stoneydsp::int64 deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

//=======================================================//boundary_and_overflow

TEST_CASE ("Boundary and overflow behaviour of stoneydsp::int64",
           "[boundary][overflow][int64]")
{
  ::stoneydsp::int64 a = 9223372036854775807LL;
  ::stoneydsp::int64 b = 1;
  REQUIRE (
      static_cast< ::stoneydsp::int64> (a + b)
      == ::std::numeric_limits<
          ::stoneydsp::int64>::min ()); // Check overflow wrap-around behaviour
}

//======================================================//boundary_and_underflow

TEST_CASE ("Boundary and underflow behavior of stoneydsp::int64",
           "[boundary][underflow][int64]")
{
  ::stoneydsp::int64 a = -9223372036854775807LL - 1;
  ::stoneydsp::int64 b = 1;
  REQUIRE (static_cast< ::stoneydsp::int64> (a - b)
           == 9223372036854775807LL); // Check underflow wrap-around behavior
}

//===============================================================//compatibility

TEST_CASE ("Compatibility of stoneydsp::int64 with standard library",
           "[compatibility][int64]")
{
  ::std::vector< ::stoneydsp::int64> vec = { 5, 3, 4, 1, 2 };

  // Use std::sort to sort the vector
  ::std::sort (vec.begin (), vec.end ());

  // Verify the vector is sorted
  REQUIRE (vec == ::std::vector< ::stoneydsp::int64>{ 1, 2, 3, 4, 5 });

  // Use std::accumulate to sum the elements
  ::stoneydsp::int64 sum
      = ::std::accumulate (vec.begin (), vec.end (), ::stoneydsp::int64 (0));

  // Verify the sum is correct
  REQUIRE (sum == 15);
}

//===================================================================//benchmark

// Benchmark for addition
TEST_CASE ("Benchmark for stoneydsp::int64 addition", "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 1200;
  ::stoneydsp::int64 b = 3400;

  BENCHMARK ("Addition") { return a + b; };
}

// Benchmark for subtraction
TEST_CASE ("Benchmark for stoneydsp::int64 subtraction", "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 3400;
  ::stoneydsp::int64 b = 1200;

  BENCHMARK ("Subtraction") { return a - b; };
}

// Benchmark for multiplication
TEST_CASE ("Benchmark for stoneydsp::int64 multiplication",
           "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 1200;
  ::stoneydsp::int64 b = 2;

  BENCHMARK ("Multiplication") { return a * b; };
}

// Benchmark for division
TEST_CASE ("Benchmark for stoneydsp::int64 division", "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 1200;
  ::stoneydsp::int64 b = 2;

  BENCHMARK ("Division") { return a / b; };
}

// Benchmark for type conversion to int
TEST_CASE ("Benchmark for stoneydsp::int64 to int conversion",
           "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 1200;

  BENCHMARK ("Conversion to int") { return static_cast<int> (a); };
}

// Benchmark for type conversion to float
TEST_CASE ("Benchmark for stoneydsp::int64 to float conversion",
           "[benchmark][int64]")
{
  ::stoneydsp::int64 a = 1200;

  BENCHMARK ("Conversion to float")
  {
    return static_cast< ::stoneydsp::float_t> (a);
  };
}

//============================================================================//

#endif // defined(STONEYDSP_BUILD_TEST)

//=========================================================================//EOF
