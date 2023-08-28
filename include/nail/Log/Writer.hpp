// Writer.hpp
// 27 Apr 2021
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_WRITER_HPP
#define NAIL_WRITER_HPP

#include <string_view>

#include "nail/Log/Logger.hpp"

namespace nail
{
    class Writer
    {
    public:
       virtual void write(Logger::Level level, std::string_view line) = 0;

       virtual ~Writer() = default;
    };
}

#endif // NAIL_WRITER_HPP
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

