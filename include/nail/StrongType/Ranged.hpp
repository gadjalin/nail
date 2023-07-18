// Ranged.hpp
// 1 Apr 2021
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_RANGED_HPP
#define NAIL_RANGED_HPP

#include <type_traits>
#include <fmt/format.h>

namespace nail
{
    template<typename Type, Type Min, Type Max, Type Default = Min>
    class Ranged
    {
        static_assert(std::is_arithmetic_v<Type>);
        static_assert(Min < Max);
        static_assert(Default >= Min && Default <= Max);

    public:
        using ValueType = Type;

    public:
        operator Type() const noexcept;

        Ranged() noexcept;
        // TODO: Make constexpr
        Ranged(Type const& value);
        Ranged(Type&& value);

        Ranged& operator=(Type const& value);
        Ranged& operator=(Type&& value);

    private:
        constexpr bool isInRange(Type const& value) const noexcept;
        [[noreturn]] void defaultsAndThrow(Type const& badValue);

        Type m_value;
    };

    template<int32_t Min, int32_t Max, int32_t Default = Min>
    using RangedInt = Ranged<int32_t, Min, Max, Default>;

    template<uint32_t Min, uint32_t Max, uint32_t Default = Min>
    using RangedUnsigned = Ranged<uint32_t, Min, Max, Default>;
}

#include "Ranged.inl"

#endif // NAIL_RANGED_HPP
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

