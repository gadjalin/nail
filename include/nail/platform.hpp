#ifndef NAIL_PLATFORM_HPP
#define NAIL_PLATFORM_HPP

// Platform detection
#if defined(_WIN64) // Windows 64bit
#   define NAIL_PLATFORM_WINDOWS
#   ifdef _MSC_VER
#       pragma warning(disable: 4251)
#   endif
#elif defined(__ANDROID__) // Android
#   define NAIL_PLATFORM_ANDROID
#   error "Android platform not supported !"
#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__)) // Linux 64bit
#   define NAIL_PLATFORM_LINUX
#elif defined(__APPLE__) || defined(__MACH__) // Apple
#   include <TargetConditionals.h>
#   if TARGET_RT_64_BIT == 0
#       error "32-bit platforms are not supported !"
#   elif TARGET_OS_MAC == 1
#       if TARGET_OS_IPHONE == 1
#           define NAIL_PLATFORM_IPHONE
#           error "iPhone platform not supported !"
#       else
#           define NAIL_PLATFORM_MACOS
#       endif
#   else
#       error "Unsupported Apple platform"
#   endif
#else
#   error "32-bit platforms are not supported !"
#endif // Platform detection

// DLL/SO symbol visibility
#if __GNUC__ >= 4 || defined(__clang__) // GNU GCC __attribute__
#   define NAIL_API __attribute__((visibility("default")))
#   define NAIL_HIDDEN __attribute__((visibility("hidden")))
#else
#   define NAIL_API
#   define NAIL_HIDDEN
#endif // DLL/SO symbol visibility

#endif // NAIL_PLATFORM_HPP

