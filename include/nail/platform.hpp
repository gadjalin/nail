// platform.hpp
// 27 Nov 2020
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_PLATFORM_HPP
#define NAIL_PLATFORM_HPP

// Platform detection
#if defined(_WIN32) // Windows

    #if defined(_WIN64)
        #define NAIL_PLATFORM_WINDOWS
    #else
        #error "32bit platforms are not supported!"
    #endif

#elif defined(__ANDROID__) // Android

    #define NAIL_PLATFORM_ANDROID
    #error "Android platform not supported!"

#elif defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__)) // Linux

    #define NAIL_PLATFORM_LINUX

#elif defined(__APPLE__) && defined(__MACH__) // Mac/iPhone

    #include <TargetConditionals.h>

    #if TARGET_RT_64_BIT == 1
        #if TARGET_OS_OSX

            #define NAIL_PLATFORM_MACOS

        #elif TARGET_OS_IPHONE

            #define NAIL_PLATFORM_IPHONE
            #error "iOs platform not supported!"

        #else

            #error "Unsupported Apple platform"

        #endif
    #else
        #error "32bit platforms are not supported!"
    #endif

#else

    #error "Unsupported platform!"

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

