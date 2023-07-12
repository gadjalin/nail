// Logger.hpp
// 1 Dec 2020
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_LOGGER_HPP
#define NAIL_LOGGER_HPP

#include <string>
#include <unordered_set>
#include <fmt/format.h>

#include "nail/defines.hpp"

#define NAIL_LOGGER_MAXIDSIZE 15

namespace nail
{
    class Writer;

    class NAIL_API Logger
    {
    public:
        enum Level : uint8_t
        {
            Debug = 0,
            Info,
            Warn,
            Error,
            Critical
        };

        template<typename... Args>
        void log(Level level, std::string_view fmt, Args&&... args);

        template<typename... Args>
        void debug(std::string_view fmt, Args&&... args);
        template<typename... Args>
        void info(std::string_view fmt, Args&&... args);
        template<typename... Args>
        void warn(std::string_view fmt, Args&&... args);
        template<typename... Args>
        void error(std::string_view fmt, Args&&... args);
        template<typename... Args>
        void critical(std::string_view fmt, Args&&... args);

        void addWriter(Writer& writer);
        void removeWriter(Writer& writer);

        void setLogLevel(Level level) noexcept;
        Level getLogLevel() const noexcept;

        std::string const& getID() const noexcept;

        template<size_t IdSize>
        explicit Logger(char const (&id)[IdSize], Level logLevel = Level::Info);

    private:
        void write(Level level, std::string_view line);

        std::string const m_id;
        Level m_logLevel;
        std::unordered_set<Writer*> m_writers;
    };
}

#include "Logger.inl"

#endif // NAIL_LOGGER_HPP
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

