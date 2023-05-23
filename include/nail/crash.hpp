// Crash.hpp
// 22 May 2023
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_CRASH_HPP
#define NAIL_CRASH_HPP

#if defined(_WIN32) && defined(__has_include) && __has_include(<intrin.h>)
    #define NAIL_USE_DEBUGBREAK
#elif defined(__GNUC__) || defined(__clang__)
    #define NAIL_USE_TRAP
#endif

#include <cstdlib>

#if defined(NAIL_USE_DEBUGBREAK)
    #include <intrin.h>
#endif

namespace nail
{
    [[noreturn]]
    inline void crash() noexcept
    {
    #if defined(NAIL_USE_DEBUGBREAK)
        ::__debugbreak();
    #elif defined(NAIL_USE_TRAP)
        __builtin_trap();
    #else
        ::std::abort();
    #endif
    }
}

#endif // NAIL_CRASH_HPP
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

