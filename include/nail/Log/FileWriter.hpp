// FileWriter.hpp
// 12 Jul 2023
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_FILEWRITER_HPP
#define NAIL_FILEWRITER_HPP

#include <cstdio>
#include <string_view>

#include "nail/defines.hpp"
#include "nail/Common/NonCopyable.hpp"
#include "nail/Log/Logger.hpp"
#include "nail/Log/Writer.hpp"

namespace nail
{
    class NAIL_API FileWriter : public Writer, NonCopyable, NonMovable
    {
    public:
        void write(Logger::Level level, std::string_view line) override;

        std::string const& getFilePath() const noexcept;

        explicit FileWriter(std::string_view filepath);
        ~FileWriter();

    private:
        std::string const m_filepath;
        std::FILE* m_file;
    };
}

#include "FileWriter.inl"

#endif // NAIL_FILEWRITER_HPP
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

