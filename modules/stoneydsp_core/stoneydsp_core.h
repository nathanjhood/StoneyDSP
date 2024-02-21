/**
 * @file stoneydsp_core.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#define __STONEYDSP_CORE_H__

#include "version/stoneydsp_version.h"

#ifndef STRINGIFY
# define STRINGIFY_HELPER(n) #n
# define STRINGIFY(n) STRINGIFY_HELPER(n)
#endif

/* Compatibility for non-Clang compilers */
#ifndef __has_declspec_attribute
#  define __has_declspec_attribute(x) 0
#endif

#ifdef __cplusplus
# define STONEYDSP_USING_CXX 1
#else
# define STONEYDSP_USING_CXX 0
#endif

#if STONEYDSP_USING_CXX
/**
 * @brief The ```StoneyDSP``` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
# define STONEYDSP_BEG_NAMESPACE namespace StoneyDSP {
# define STONEYDSP_END_NAMESPACE } // namespace StoneyDSP

/**
 * @brief The ```StoneyDSP``` C declarations.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
# define STONEYDSP_BEG_EXTERN_DECLS extern "C" {
# define STONEYDSP_END_EXTERN_DECLS } // extern "C"

#else

# define STONEYDSP_BEG_NAMESPACE
# define STONEYDSP_END_NAMESPACE
# define STONEYDSP_BEG_EXTERN_DECLS
# define STONEYDSP_END_EXTERN_DECLS

#endif



#undef STONEYDSP

#if STONEYDSP_USING_CXX
STONEYDSP_BEG_EXTERN_DECLS
#endif

/**
 * @brief The ```__STONEYDSP``` pre-processor macro.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 *
 */
#define __STONEYDSP void

/**
 * @brief The ```STONEYDSP``` pre-processor macro.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 *
 */
#define STONEYDSP __STONEYDSP

/**
 * @brief The ```__stoneydsp``` typedef.
 * @typedef ```void````
 *
 */
typedef STONEYDSP __stoneydsp;

/**
 * @brief The ```__stoneydsp_ptr``` typedef.
 * @typedef ```__stoneydsp*```
 *
 */
typedef __stoneydsp* __stoneydsp_ptr;

typedef int 		__stoneydsp_version_number;
typedef const char* __stoneydsp_version_string;

typedef const __stoneydsp_version_number __stoneydsp_version_major;
typedef const __stoneydsp_version_number __stoneydsp_version_minor;
typedef const __stoneydsp_version_number __stoneydsp_version_patch;
typedef const __stoneydsp_version_string __stoneydsp_version_tweak;


typedef struct {
	const __stoneydsp_version_major _major;
	const __stoneydsp_version_minor _minor;
	const __stoneydsp_version_patch _patch;
	const __stoneydsp_version_tweak _tweak;
}
/**
 * @brief The ```__stoneydsp_version```  struct.
 *
 */
__stoneydsp_version;

/**
 * @brief The ```__stoneydsp_stoneydsp``` typedef.
 * @typedef ```__stoneydsp```
 *
 */
typedef __stoneydsp __stoneydsp_stoneydsp;

/**
 * @brief The ```__stoneydsp_stoneydsp_ptr``` typedef.
 * @typedef ```__stoneydsp_ptr```
 *
 */
typedef __stoneydsp_ptr __stoneydsp_stoneydsp_ptr;



/**
 * @brief The ```stoneydsp``` object.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 *
 */
const __stoneydsp* stoneydsp;

const __stoneydsp_version_major stoneydsp_version_major = STONEYDSP_VERSION_MAJOR;
const __stoneydsp_version_minor stoneydsp_version_minor = STONEYDSP_VERSION_MINOR;
const __stoneydsp_version_patch stoneydsp_version_patch = STONEYDSP_VERSION_PATCH;
const __stoneydsp_version_tweak stoneydsp_version_tweak = STONEYDSP_VERSION_TWEAK;

#if STONEYDSP_USING_CXX
STONEYDSP_END_EXTERN_DECLS
#endif

#include "res/stoneydsp_resource.h"
#include "types/stoneydsp_types.h"



#if STONEYDSP_USING_CXX
/**
 * @brief The ```StoneyDSP``` namespace.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
STONEYDSP_BEG_NAMESPACE
#endif

/**
 * @brief The ```StoneyDSP::StoneyDSP``` object.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
const __stoneydsp_stoneydsp* StoneyDSP;

/**
 * @brief The ```StoneyDSP::StoneyDSPPtr``` object.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
const __stoneydsp_stoneydsp_ptr StoneyDSPPtr = &StoneyDSP;

/**
 * @brief The ```StoneyDSP::Versions```  struct.
 * @details Provides an alias to the current ```stoneydsp_version_*```.
 * @namespace StoneyDSP
 *
 */
struct Versions {
	typedef __stoneydsp_version_major _Major;
	typedef __stoneydsp_version_minor _Minor;
	typedef __stoneydsp_version_patch _Patch;
	typedef __stoneydsp_version_tweak _Tweak;

	_Major   major;
	_Minor   minor;
	_Patch   patch;
	_Tweak   tweak;
};

/**
 * @brief The current ```stoneydsp_version```  struct.
 * @author Nathan J. Hood (nathanjhood@googlemail.com)
 * @copyright Copyright (c) 2024
 * @namespace StoneyDSP
 *
 */
const Versions stoneydsp_version = {
	stoneydsp_version_major,
	stoneydsp_version_minor,
	stoneydsp_version_patch,
	stoneydsp_version_tweak
};

/**
 * @brief The current ```StoneyDSP::Version```  struct.
 * @details Provides an alias to ```stoneydsp_version```.
 * @namespace StoneyDSP
 *
 */
const Versions Version = stoneydsp_version;

STONEYDSP_END_NAMESPACE
