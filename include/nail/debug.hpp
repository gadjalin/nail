// debug.hpp
// 21 May 2023
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_DEBUG_HPP
#define NAIL_DEBUG_HPP

#include <string_view>

#if defined(__clang__)
    #define __FILENAME__ __FILE_NAME__
#elif defined(_WIN32)
    #define __FILENAME__ \
        (std::string_view(__FILE__).find_last_of('\\') != std::string_view::npos ? \
        (char const*) __FILE__ + std::string_view(__FILE__).find_last_of('\\') + 1 : __FILE__)
#else
    #define __FILENAME__ \
        (std::string_view(__FILE__).find_last_of('/') != std::string_view::npos ? \
        (char const*) __FILE__ + std::string_view(__FILE__).find_last_of('/') + 1 : __FILE__)
#endif

// TODO: Cpp20 std::source_location
namespace nail
{
    struct SourceLocation
    {
        char const* file;
        unsigned int line;
        char const* function;
    };
}

#define CURRENT_SOURCE_LOCATION nail::SourceLocation{__FILENAME__, static_cast<unsigned int>(__LINE__), __func__ }

#endif // NAIL_DEBUG_HPP
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
