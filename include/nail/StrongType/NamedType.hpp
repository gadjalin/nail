// NamedType.hpp
// Gaétan "Gad" Jalin
// 11 May 2022
// See end of file for complete licence description
#ifndef NAIL_NAMEDTYPE_HPP
#define NAIL_NAMEDTYPE_HPP

// Inspired by https://fluentcpp.com articles on Strong Types

#include <memory>
#include <type_traits>

namespace nail
{
    template<typename Underlying, typename Tag>
    class NamedType
    {
    public:
        Underlying& get() noexcept;
        Underlying const& get() const noexcept;

        explicit NamedType(Underlying const& value);
        template<typename T = Underlying, typename = typename std::enable_if_t<!std::is_reference_v<T> > >
        explicit NamedType(Underlying&& value);

        Underlying* operator->() noexcept;
        Underlying const* operator->() const noexcept;

        Underlying& operator*() & noexcept;
        Underlying const& operator*() const& noexcept;

        Underlying&& operator*() && noexcept;
        Underlying const&& operator*() const&& noexcept;

    private:
        Underlying m_value;
    };
}

#include "NamedType.inl"

#endif // NAIL_NAMEDTYPE_HPP
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

