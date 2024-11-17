// Algorithm.inl
// 17 Nov 2024
// Gaétan J.A.M. Jalin
// See end of file for complete license description
template<typename InputIt, typename BinaryFn>
inline BinaryFn nail::compare_each(InputIt first, InputIt const last, BinaryFn f)
{
    for (; first != last; ++first)
        for (auto against = std::next(first); against != last; ++against)
            f(*first, *against);

    return f;
}

template<typename InputIt, typename BinaryPred>
inline std::pair<InputIt, InputIt> nail::find_if_compare(InputIt first, InputIt const last, BinaryPred p)
{
    for (; first != last; ++first)
        for (auto against = std::next(first); against != last; ++against)
            if (p(*first, *against))
                return {first, against};

    return {last, last};
}

template<typename InputIt, typename BinaryPred>
inline std::pair<InputIt, InputIt> nail::find_if_not_compare(InputIt first, InputIt const last, BinaryPred p)
{
    for (; first != last; ++first)
        for (auto against = std::next(first); against != last; ++against)
            if (!p(*first, *against))
                return {first, against};

    return {last, last};
}

template<typename InputIt, typename BinaryPred>
inline bool nail::compare_all_of(InputIt first, InputIt const last, BinaryPred p)
{
    return find_if_not_compare(first, last, p).first == last;
}

template<typename InputIt, typename BinaryPred>
inline bool nail::compare_any_of(InputIt first, InputIt const last, BinaryPred p)
{
    return find_if_compare(first, last, p).first != last;
}

template<typename InputIt, typename BinaryPred>
inline bool nail::compare_none_of(InputIt first, InputIt const last, BinaryPred p)
{
    return find_if_compare(first, last, p).first == last;
}

/**
 * Copyright (C) 2020-2024 Gaétan Jalin
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

