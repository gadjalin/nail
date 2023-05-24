/**
 * C++ 17
 * Header-only tee debugging tool.
 *
 * Based on the "tee" unix command, this debugging tool is used
 * to print variables for debugging in a simple, non invasive, readable way.
 *
 *           []================[]
 *          -->    ------>    --->
 *           []=====| | |======[]
 *                  | v |
 *                  |   |   ___   ___
 *                  |   |  |     |
 *                  |   |  |==   |==
 *                  |   |  |___  |___
 *                 || | ||
 *                    v
 *
 **/
// Tee.hpp
// 31 Aug 2020
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_TEE_HPP
#define NAIL_TEE_HPP

#include <iostream>
#include <fstream>
#include <type_traits>
#include <utility>

namespace nail
{
    template<typename Print>
    class Tee
    {
    public:
        template<typename V>
        auto operator()(V&& value) const -> decltype(std::forward<V>(value));

        constexpr explicit Tee(Print print);

    private:
        Print m_print;
    };

    // File output specialisation
    template<>
    class Tee<char const*>
    {
    public:
        template<typename V>
        auto operator()(V&& value) const -> decltype(std::forward<V>(value));

        constexpr explicit Tee(char const* file);

    private:
        char const* m_path;
    };

    // Stream output specialisation
    template<>
    class Tee<std::ostream>
    {
    public:
        template<typename V>
        auto operator()(V&& value) const -> decltype(std::forward<V>(value));

        constexpr explicit Tee(std::ostream& os);

    private:
        std::ostream& m_os;
    };

    template<typename Print>
    constexpr Tee<Print> make_tee(Print print);

    constexpr Tee<std::ostream> make_tee(std::ostream& os);

    constexpr Tee<char const*> make_tee(char const* file);
}

template<typename V, typename TeeType>
auto operator|(V const&& value, nail::Tee<TeeType> const& tee_) -> decltype(std::forward<V>(value));

#include "Tee.inl"

// Default tee
constexpr nail::Tee<std::ostream> stdtee = nail::make_tee(std::cout);
constexpr nail::Tee<std::ostream> errtee = nail::make_tee(std::cerr);

#endif // NAIL_TEE_HPP
/*
 * Copyright (C) 2020-2023 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

