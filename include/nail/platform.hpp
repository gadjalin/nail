// platform.hpp
// 27 Nov 2020
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_PLATFORM_HPP
#define NAIL_PLATFORM_HPP

// Platform detection
#if defined(_WIN64) // Windows 64bit
    #define NAIL_PLATFORM_WINDOWS
//    #ifdef _MSC_VER
//        #pragma warning(disable: 4251)
//    #endif
#elif defined(__ANDROID__) // Android
    #define NAIL_PLATFORM_ANDROID
    #error "Android platform not supported !"
#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__)) // Linux 64bit
    #define NAIL_PLATFORM_LINUX
#elif defined(__APPLE__) || defined(__MACH__) // Apple
    #include <TargetConditionals.h>
    #if TARGET_RT_64_BIT == 0
        #error "32-bit platforms are not supported !"
    #elif TARGET_OS_MAC == 1
        #if TARGET_OS_IPHONE == 1
            #define NAIL_PLATFORM_IPHONE
            #error "iPhone platform not supported !"
        #else
            #define NAIL_PLATFORM_MACOS
        #endif
    #else
        #error "Unsupported Apple platform"
    #endif
#else
    #error "32-bit platforms are not supported !"
#endif // Platform detection

#endif // NAIL_PLATFORM_HPP
/**
 * Copyright (C) 2020-2023 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/

