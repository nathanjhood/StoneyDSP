#include <sstream>

namespace stoneydsp
{
namespace test
{
/**
 * @brief
 *
 * @tparam T
 * @param originalValue
 *
 *
 * @example
 * ```cpp
 * TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8",
 * "[serialization][uint8]")
 * {
 *   testSerialization< ::stoneydsp::uint8> (123);
 * }
 * ```
 */
template <typename T>
void
testSerialization (const T &originalValue)
{
  ::std::stringstream ss;
  T deserializedValue;

  ss.write (reinterpret_cast<const char *> (&originalValue),
            sizeof (originalValue));
  ss.read (reinterpret_cast<char *> (&deserializedValue),
           sizeof (deserializedValue));

  REQUIRE (originalValue == deserializedValue);
}

}
}

// TEST_CASE ("Check serialization and deserialization for stoneydsp::uint8",
//            "[serialization][uint8]")
// {
//   testSerialization< ::stoneydsp::uint8> (123);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::uint16",
//            "[serialization][uint16]")
// {
//   testSerialization< ::stoneydsp::uint16> (12345);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::uint32",
//            "[serialization][uint32]")
// {
//   testSerialization< ::stoneydsp::uint32> (123456789);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::uint64",
//            "[serialization][uint64]")
// {
//   testSerialization< ::stoneydsp::uint64> (1234567890123456789ULL);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::int8",
//            "[serialization][int8]")
// {
//   testSerialization< ::stoneydsp::int8> (-123);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::int16",
//            "[serialization][int16]")
// {
//   testSerialization< ::stoneydsp::int16> (-12345);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::int32",
//            "[serialization][int32]")
// {
//   testSerialization< ::stoneydsp::int32> (-123456789);
// }

// TEST_CASE ("Check serialization and deserialization for stoneydsp::int64",
//            "[serialization][int64]")
// {
//   testSerialization< ::stoneydsp::int64> (-1234567890123456789LL);
// }
