// String.cpp
// 17 Nov 2024
// Gaétan J.A.M Jalin
// See end of file for complete license description
#include "nail/Utils/String.hpp"

#include <vector>
#include <deque>
#include <forward_list>
#include <list>

namespace nail
{
    std::string join(std::string const& lhs, std::string const& rhs, std::string const& delimiter)
    {
        return lhs + delimiter + rhs;
    }

    template std::string
    join_all<std::vector<std::string>::const_iterator>(std::vector<std::string>::const_iterator first,
                                                       std::vector<std::string>::const_iterator last,
                                                       std::string const& delimiter);

    template std::string
    join_all<std::deque<std::string>::const_iterator>(std::deque<std::string>::const_iterator first,
                                                      std::deque<std::string>::const_iterator last,
                                                      std::string const& delimiter);

    template std::string
    join_all<std::list<std::string>::const_iterator>(std::list<std::string>::const_iterator first,
                                                     std::list<std::string>::const_iterator last,
                                                     std::string const& delimiter);

    template std::string
    join_all<std::forward_list<std::string>::const_iterator>(std::forward_list<std::string>::const_iterator first,
                                                             std::forward_list<std::string>::const_iterator last,
                                                             std::string const& delimiter);
}

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
