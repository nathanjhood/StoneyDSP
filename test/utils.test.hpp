/**
 * @file utils.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @date 2025-02-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_TEST_UTILS_H_INCLUDED
  #define STONEYDSP_TEST_UTILS_H_INCLUDED

  #include "stoneydsp/core/core.h" // for `STONEYDSP_PUBLIC_FUNCTION`

  #include <sstream>

namespace stoneydsp
{
namespace test
{

/**
 * @brief
 *
 * @tparam T
 * @param expectedSizeof
 *
 */
template <typename T>
void STONEYDSP_PUBLIC_FUNCTION testSizeof (const T &expectedSizeof);

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
void STONEYDSP_PUBLIC_FUNCTION testSerialization (const T &originalValue);

} // namespace test

} // namespace stoneydsp

#endif // STONEYDSP_TEST_UTILS_H_INCLUDED
