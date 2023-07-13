#include "nail/Log/Logger.hpp"

#include <ctime>
#include <fmt/chrono.h>

#include "nail/Log/Writer.hpp"
#include "nail/Debug/Assert.hpp"

#define NAIL_LOGGER_MAXIDSIZE 15

namespace nail
{
    namespace details
    {
        static constexpr char const* levelToString[5] = {"Debug", "Info", "Warning", "Error", "Critical"};
    }

    std::unordered_map<std::string, std::shared_ptr<Logger> > Logger::s_loggers;

    Logger::Logger(std::string const& id, Level const logLevel)
        : m_id(id), m_logLevel(logLevel)
    {
        NAIL_DEBUG_ASSERT(id.size() > 2 && id.size() <= NAIL_LOGGER_MAXIDSIZE, "Logger ID is of incorrect size !");
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

    void Logger::addWriter(std::shared_ptr<Writer> writer)
    {
        m_writers.insert(writer);
    }

    void Logger::removeWriter(std::shared_ptr<Writer> writer)
    {
        m_writers.erase(writer);
    }

    void Logger::clearWriters() noexcept
    {
        m_writers.clear();
    }

    void Logger::setLogLevel(Level const level) noexcept
    {
        m_logLevel = level;
    }

    std::shared_ptr<Logger> Logger::Create(std::string const& id,
                                           Level const logLevel)
    {
        return TryCreate(id, logLevel);
    }

    std::shared_ptr<Logger> Logger::Create(std::string const& id,
                                           std::shared_ptr<Writer> writer,
                                           Level const logLevel)
    {
        auto logger = TryCreate(id, logLevel);

        logger->addWriter(std::move(writer));

        return logger;
    }

    std::shared_ptr<Logger> Logger::Create(std::string const& id,
                                           std::initializer_list<std::shared_ptr<Writer> > writers,
                                           Level const logLevel)
    {
        auto logger = TryCreate(id, logLevel);

        for (auto& writer : writers)
            logger->addWriter(writer);

        return logger;
    }

    std::shared_ptr<Logger> Logger::TryCreate(std::string const& id, Level const logLevel)
    {
        if (s_loggers.find(id) != s_loggers.end())
            throw std::runtime_error(fmt::format("Logger with name {} already exists!", id));

        auto logger = std::make_shared<Logger>(id, logLevel);
        s_loggers.emplace(id, logger);

        return logger;
    }

    std::shared_ptr<Logger> Logger::Get(std::string const& id)
    {
        auto foundLogger = s_loggers.find(id);
        return (foundLogger != s_loggers.end()) ? foundLogger->second : nullptr;
    }

    void Logger::Delete(std::string const& id)
    {
        s_loggers.erase(id);
    }

    void Logger::DeleteAll() noexcept
    {
        s_loggers.clear();
    }
}

