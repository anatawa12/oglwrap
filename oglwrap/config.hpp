/** @file config.hpp
    @brief Contains macros to configure oglwrap.
*/

#ifndef OGLWRAP_CONFIG_HPP_
#define OGLWRAP_CONFIG_HPP_

/// A macro to sign functions that are bind-checked in their signature.
#define BIND_CHECKED

/// A macro for internal use only
#ifdef GL_LINE
  #define OGLWRAP_OPENGL_INCLUDED 1
#else
  #define OGLWRAP_OPENGL_INCLUDED 0
#endif

/// If true, loads only the extensions, that are available.
/** By default, it's only turned on, if a GL header is included. */
#ifndef OGLWRAP_CHECK_DEPENDENCIES
  #if OGLWRAP_OPENGL_INCLUDED // If an OpenGL header is loaded.
    #define OGLWRAP_CHECK_DEPENDENCIES 1
  #else // else all #if defined(gl*) would evaluate as false, so better just disable dependency check
    #define OGLWRAP_CHECK_DEPENDENCIES 0
  #endif
#endif

/// If true, enables error checking, and DebugOutputs.
#ifndef OGLWRAP_DEBUG
  #define OGLWRAP_DEBUG 1
#endif

/// If true, warns you if you call a function that requires binding, through an object that isn't the currently bound one.
#if OGLWRAP_DEBUG
  #ifndef OGLWRAP_BINDCHECK
    #define OGLWRAP_BINDCHECK 1
  #endif
#endif

/// If set to true, disable the oglwrap debug output.
/** Setting OGLWRAP_DEBUG flag to true will override this flag, and will turn the debug output off */
#ifndef OGLWRAP_DISABLE_DEBUG_OUTPUT
  #define OGLWRAP_DISABLE_DEBUG_OUTPUT 0
#endif

/// If true, uses Magick++ API to load images.
#ifndef OGLWRAP_USE_IMAGEMAGICK
  #define OGLWRAP_USE_IMAGEMAGICK 0
#endif

/// If true, sacrifices a bit of performance, to increase portability.
/** For example, excludes codes that do not work well with dual-gpu
  * systems, but are definitely faster on most configurations. */
#ifndef OGLWRAP_PORTABILITY_MODE
  #define OGLWRAP_PORTABILITY_MODE 1
#endif

/// Oglwrap can be forced to load glew. 
#ifndef OGLWRAP_USE_GLEW
  #define OGLWRAP_USE_GLEW 0
#endif

#if OGLWRAP_USE_GLEW
  #include "glew.hpp"
#endif

#endif // OGLWRAP_CONFIG_HPP_
