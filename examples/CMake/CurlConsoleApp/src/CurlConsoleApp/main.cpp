/***************************************************************************//**
 * @file main.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 *
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/


#include "CurlConsoleApp/main.h"

#include <juce_core/juce_core.h>

#include <stoneydsp_core/stoneydsp_core.h>
#include <stoneydsp_web/stoneydsp_web.h>

int Main(int argc, char* argv[])
{
    juce::ignoreUnused(argc);

    // for(int i = 0; i < argc; ++i)
    //     std::cout << "Argument " << i << ": " << argv[i] << std::endl;

    return StoneyDSP::Web::Http::Get(argv[1], 1L);
}
