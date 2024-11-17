// String.inl
// 17 Nov 2024
// Gaétan J.A.M Jalin
// See end of file for complete license description
template<typename InputIt>
inline auto nail::join_all(InputIt first, InputIt last, std::string const& delimiter)
    -> std::enable_if_t<std::is_same_v<typename std::iterator_traits<InputIt>::value_type, std::string>, std::string>
{
    NAIL_DEBUG_ASSERT(first != last, "Cannot join an empty list of strings!");
    return std::accumulate(std::next(first), last, *first,
        [&delimiter](std::string const& lhs, std::string const& rhs) -> std::string
        {
            return join(lhs, rhs, delimiter);
        });
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

