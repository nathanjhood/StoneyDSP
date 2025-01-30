/**
 * @file cxx.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef STONEYDSP_CXX_H_INCLUDED
#define STONEYDSP_CXX_H_INCLUDED

//==============================================================================

/**
 * @brief This is a shorthand macro for deleting a class's constructor.
 *
 */
#define STONEYDSP_DECLARE_NON_CONSTRUCTABLE(className) \
  className () = delete;

//==============================================================================

/**
 * @brief This is a shorthand macro for deleting a class's copy constructor
 * and copy assignment operator.
 *
 */
#define STONEYDSP_DECLARE_NON_COPYABLE(className) \
  className (const className&) = delete;\
  className& operator= (const className&) = delete;

//==============================================================================

/**
 * @brief This is a shorthand macro for deleting a class's move constructor
 * and move assignment operator.
 *
 */
#define STONEYDSP_DECLARE_NON_MOVEABLE(className) \
  className (className&&) = delete;\
  className& operator= (className&&) = delete;

//==============================================================================

/**
 * @brief This macro can be added to class definitions to disable the use of
 * new/delete to allocate the object on the heap, forcing it to only be used
 * as a stack or member variable.
 *
 */
#define STONEYDSP_PREVENT_HEAP_ALLOCATION \
private: \
  static void* operator new (size_t) = delete; \
  static void operator delete (void*) = delete;

//==============================================================================

#endif // STONEYDSP_CXX_H_INCLUDED

//==============================================================================
