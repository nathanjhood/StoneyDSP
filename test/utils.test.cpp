#include <catch2/catch_test_macros.hpp>

#include "utils.test.hpp"

#include <sstream>

template <typename T>
void
STONEYDSP_PUBLIC_FUNCTION ::stoneydsp::test::testSizeof (
    const T &expectedSizeof)
{
  REQUIRE (sizeof (T) == expectedSizeof);
}

template <typename T>
void
STONEYDSP_PUBLIC_FUNCTION ::stoneydsp::test::testSerialization (
    const T &originalValue)
{
  ::std::stringstream ss;
  T deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}
