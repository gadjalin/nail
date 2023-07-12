#include "nail/Log/Logger.hpp"

#include <ctime>
#include <fmt/chrono.h>

#include "nail/Log/Writer.hpp"

namespace nail
{
    namespace details
    {
        static constexpr char const* levelToString[5] = {"Debug", "Info", "Warning", "Error", "Critical"};
    }

    void Logger::write(Level const level, std::string_view const line)
    {
        bool const canLog = (level >= m_logLevel && !m_writers.empty());
        if (!canLog) return;

        std::time_t const t = time(nullptr);
        std::tm const* tmb = std::localtime(&t);
        std::string const formattedLine = fmt::format("[{:%H:%M:%S}] [{}] <{}> {}", *tmb, details::levelToString[level], m_id, line);

        for (auto& writer : m_writers)
            writer->write(level, formattedLine);
    }

    void Logger::addWriter(Writer& writer)
    {
        m_writers.insert(&writer);
    }

    void Logger::removeWriter(Writer& writer)
    {
        m_writers.erase(&writer);
    }

    void Logger::setLogLevel(Level const level) noexcept
    {
        m_logLevel = level;
    }
}

