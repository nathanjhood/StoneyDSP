/***************************************************************************//**
 * @file main.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-09
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once

#define __MAIN_H__

/**
 * @brief Functions within the source program perform one or more specific
 * tasks. The 'wmain' function can call these functions to perform their
 * respective tasks. When 'wmain' calls another function, it passes execution
 * control to the function, so that execution begins at the first statement in
 * the function. A function returns control to 'wmain' when a return statement is
 * executed or when the end of the function is reached.
 *
 * @return int
 */
// Int wmain(void);

/**
 * @brief Functions within the source program perform one or more specific
 * tasks. The 'wmain' function can call these functions to perform their
 * respective tasks. When 'wmain' calls another function, it passes execution
 * control to the function, so that execution begins at the first statement in
 * the function. A function returns control to 'wmain' when a return statement is
 * executed or when the end of the function is reached.
 *
 * @param argc Number of strings in array 'argv'.
 * @param argv Array of command-line argument strings.
 * @return int
 */
int wmain(int argc, wchar_t* argv[]);

/**
 * @brief Functions within the source program perform one or more specific
 * tasks. The 'wmain' function can call these functions to perform their
 * respective tasks. When 'wmain' calls another function, it passes execution
 * control to the function, so that execution begins at the first statement in
 * the function. A function returns control to 'wmain' when a return statement is
 * executed or when the end of the function is reached.
 *
 * @param argc Number of strings in array 'argv'.
 * @param argv Array of command-line argument strings.
 * @param envp Array of environment variable strings.
 * @return int
 */
// Int wmain(Int argc, wchar_t* argv[], wchar_t* envp[]);

// /**
//  * @brief Functions within the source program perform one or more specific
//  * tasks. The 'main' function can call these functions to perform their
//  * respective tasks. When 'main' calls another function, it passes execution
//  * control to the function, so that execution begins at the first statement in
//  * the function. A function returns control to 'main' when a return statement is
//  * executed or when the end of the function is reached.
//  *
//  * @return int
//  */
// Int main(void);

/**
 * @brief Functions within the source program perform one or more specific
 * tasks. The 'main' function can call these functions to perform their
 * respective tasks. When 'main' calls another function, it passes execution
 * control to the function, so that execution begins at the first statement in
 * the function. A function returns control to 'main' when a return statement is
 * executed or when the end of the function is reached.
 *
 * @param argc Number of strings in array 'argv'.
 * @param argv Array of command-line argument strings.
 * @return int
 */
int main(int argc, char* argv[]);

// /**
//  * @brief Functions within the source program perform one or more specific
//  * tasks. The 'main' function can call these functions to perform their
//  * respective tasks. When 'main' calls another function, it passes execution
//  * control to the function, so that execution begins at the first statement in
//  * the function. A function returns control to 'main' when a return statement is
//  * executed or when the end of the function is reached.
//  *
//  * @param argc Number of strings in array 'argv'.
//  * @param argv Array of command-line argument strings.
//  * @param envp Array of environment variable strings.
//  * @return int
//  */
// Int main(Int argc, Char* argv[], Char* envp[]);

#ifdef UNICODE
 #define Main wmain
#else
 #define Main main
#endif

/**
 * @brief The global namespace.
 *
 */
namespace
{

} // namespace
