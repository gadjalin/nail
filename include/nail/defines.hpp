// defines.hpp
// 27 Nov 2020
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_DEFINES_HPP
#define NAIL_DEFINES_HPP

// Utilities
#define NAIL_BIT(shift) (1 << shift)

#define NAIL_TOSTRING(x) NAIL_TOSTRING_(x)
#define NAIL_TOSTRING_(x) #x

#define NAIL_CONCAT(a, b) NAIL_CONCAT_(a, b)
#define NAIL_CONCAT_(a, b) a##b

// DLL/SO symbol visibility
// Note: The CMake files have not been made to handle DLL yet, but leaves the
// door open
#if defined(_WIN32) && defined(NAIL_BUILD_DLL)
    #define NAIL_API __declspec(dllexport)
    #define NAIL_HIDDEN
#elif defined(_WIN32) && defined(NAIL_LINK_DLL)
    #define NAIL_API __declspec(dllimport)
    #define NAIL_HIDDEN
#elif __GNUC__ >= 4 || defined(__clang__)
    #define NAIL_API __attribute__((visibility("default")))
    #define NAIL_HIDDEN __attribute__((visibility("hidden")))
#else
    #define NAIL_API
    #define NAIL_HIDDEN
#endif // DLL/SO symbol visibility

//template <>
//struct fmt::formatter<std::filesystem::path>
//{
//    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
//    {
//        auto it = ctx.begin(), end = ctx.end();
//        if (it != end && *it != '}')
//            throw format_error("invalid format");
//        return it;
//    }
// 
//    template<typename FormatContext>
//    auto format(std::filesystem::path const& path, FormatContext& ctx) -> decltype(ctx.out())
//    {
//        return format_to(ctx.out(), "{}", path.string());
//    }
//};

#endif // NAIL_DEFINES_HPP
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

