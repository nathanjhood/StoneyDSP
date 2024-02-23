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

// #include "StoneyDSP/modules/stoneydsp_core/stoneydsp_core.cpp"


// #include "main.h"

#include <iostream>

int main(int argc, char* argv[])
{

    for(int i = 0; i < argc; ++i)
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;

    std::cout << std::endl;

    return 0;
}
