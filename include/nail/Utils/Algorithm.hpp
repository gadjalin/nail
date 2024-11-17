// Algorithm.hpp
// 17 Nov 2024
// Gaétan J.A.M. Jalin
// See end of file for complete license description
#ifndef NAIL_ALGORITHM_HPP
#define NAIL_ALGORITHM_HPP

#include <iterator>
#include <utility>

namespace nail
{
    template<typename InputIt, typename BinaryFn>
    BinaryFn compare_each(InputIt first, InputIt last, BinaryFn f);

    template<typename InputIt, typename BinaryPred>
    std::pair<InputIt, InputIt> find_if_compare(InputIt first, InputIt last, BinaryPred p);

    template<typename InputIt, typename BinaryPred>
    std::pair<InputIt, InputIt> find_if_not_compare(InputIt first, InputIt last, BinaryPred p);

    template<typename InputIt, typename BinaryPred>
    bool compare_all_of(InputIt first, InputIt last, BinaryPred p);

    template<typename InputIt, typename BinaryPred>
    bool compare_any_of(InputIt first, InputIt last, BinaryPred p);

    template<typename InputIt, typename BinaryPred>
    bool compare_none_of(InputIt first, InputIt last, BinaryPred p);
}

#include "Algorithm.inl"

#endif // NAIL_ALGORITHM_HPP
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

