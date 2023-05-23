// Assert.hpp
// 11 Mar 2021
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_ASSERT_HPP
#define NAIL_ASSERT_HPP

// Inspired by https://www.foonathan.net/2016/09/assertions/

#include <cstdlib>
#include <type_traits>

#include "nail/defines.hpp"
#include "nail/debug.hpp"

// Generic macro
#define NAIL_ASSERT(expression, handlerType, ...) \
    nail::Assert<handlerType>([&](void) -> bool { return (expression); }, CURRENT_SOURCE_LOCATION, #expression, __VA_ARGS__)

// For debug assertions, only evaluated when NDEBUG is not defined
#if defined(NDEBUG)
    #define NAIL_DEBUG_ASSERT(expression, message) \
        NAIL_ASSERT(expression, nail::DisabledAssertHandler, message)
#else
    #define NAIL_DEBUG_ASSERT(expression, message) \
        NAIL_ASSERT(expression, nail::EnabledAssertHandler, message)
#endif

// Always active, wether build type is debug or release
#define NAIL_ALWAYS_ASSERT(expression, message) NAIL_ASSERT(expression, nail::EnabledAssertHandler, message)

namespace nail
{
    // If Enabled
    template<typename Handler, typename Evaluator, typename... Args>
    auto Assert(Evaluator const& evaluator, SourceLocation const& location,
                char const* expression, Args&&... args) noexcept -> std::enable_if_t<Handler::enabled>;

    // If Disabled
    template<typename Handler, typename Evaluator, typename... Args>
    auto Assert(Evaluator const& evaluator, SourceLocation const& location,
                char const* expression, Args&&... args) noexcept -> std::enable_if_t<not Handler::enabled>;

    class NAIL_API EnabledAssertHandler
    {
    public:
        static constexpr bool enabled = true;
 
        [[noreturn]]
        static void Handle(SourceLocation const& location, char const* expression, char const* message) noexcept;
    };

    class DisabledAssertHandler
    {
    public:
        static constexpr bool enabled = false;
    };
}

#include "Assert.inl"

#endif // NAIL_ASSERT_HPP
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

