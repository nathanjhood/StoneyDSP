/***************************************************************************//**
 * @file stoneydsp_core.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief
 * @version 1.0.0
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/


/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 stoneydsp_core
  vendor:             stoneydsp
  version:            1.0.0
  name:               StoneyDSP core classes
  description:        The essential set of basic StoneyDSP classes, as required by all the other StoneyDSP modules.
  website:            http://stoneydsp.com
  license:            MIT
  minimumCppStandard: 17

  dependencies:       juce_core
  OSXFrameworks:      Cocoa Foundation IOKit Security
  iOSFrameworks:      Foundation
  linuxLibs:          rt dl pthread
  mingwLibs:          uuid wsock32 wininet version ole32 ws2_32 oleaut32 imm32 comdlg32 shlwapi rpcrt4 winmm

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once

#define STONEYDSP_CORE_H_INCLUDED

/**
 * @brief The ```StoneyDSP``` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */
  /// @} group StoneyDSP
} // namespace StoneyDSP

#include "version/stoneydsp_version.h"

#ifndef STRINGIFY
# define STRINGIFY_HELPER(n) #n
# define STRINGIFY(n) STRINGIFY_HELPER(n)
#endif


#include "res/stoneydsp_resource.h"
#include "types/stoneydsp_types.h"



namespace StoneyDSP
{
/** @addtogroup StoneyDSP
 *  @{
 */

/**
 * @brief The ```StoneyDSP::Core``` namespace.
 *
 */
namespace Core
{
/** @addtogroup Core
 *  @{
 */

  /// @} group Core
} // namespace Core

  /// @} group StoneyDSP
} // namespace StoneyDSP
