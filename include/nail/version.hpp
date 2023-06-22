// version.hpp
// 21 May 2023
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_VERSION_HPP
#define NAIL_VERSION_HPP

#include "nail/defines.hpp"

#define NAIL_VERSION_MAJOR 0
#define NAIL_VERSION_MINOR 1
#define NAIL_VERSION_REV 9
#define NAIL_VERSION_STAGE "a"

#define NAIL_VERSION_STRING nail::makeVersionString(NAIL_VERSION_MAJOR, NAIL_VERSION_MINOR, NAIL_VERSION_REV, NAIL_VERSION_STAGE)

namespace nail
{
    struct Version
    {
        int major;
        int minor;
        int rev;
        char const* stage;
    };

#if defined(__cpp_consteval) && __cpp_consteval >= 201811L
    consteval char const* makeVersionString(
#else
    constexpr char const* makeVersionString(
#endif
        int const major,
        int const minor,
        int const rev,
        char const* const stage) noexcept
    {
        return NAIL_TOSTRING(NAIL_VERSION_MAJOR) "-"
               NAIL_TOSTRING(NAIL_VERSION_MINOR) "."
               NAIL_TOSTRING(NAIL_VERSION_REV)
               NAIL_VERSION_STAGE;
    }

    NAIL_API Version getLibraryVersion() noexcept;
    NAIL_API char const* getLibraryVersionString() noexcept;
}

#endif // NAIL_VERSION_HPP
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

