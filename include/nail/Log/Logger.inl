template<size_t IdSize>
inline nail::Logger::Logger(char const (&id)[IdSize], Level const logLevel)
    : m_id(id), m_logLevel(logLevel)
{
    static_assert(IdSize > 2 && IdSize <= NAIL_LOGGER_MAXIDSIZE, "Logger ID is of incorrect size !");
}

template<typename... Args>
inline void nail::Logger::log(Level const level, std::string_view const fmt, Args&&... args)
{
    this->write(level, fmt::format(fmt, std::forward<Args>(args)...));
}

template<typename... Args>
inline void nail::Logger::debug(std::string_view const fmt, Args&&... args)
{
    this->log(Level::Debug, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void nail::Logger::info(std::string_view const fmt, Args&&... args)
{
    this->log(Level::Info, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void nail::Logger::warn(std::string_view const fmt, Args&&... args)
{
    this->log(Level::Warn, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void nail::Logger::error(std::string_view const fmt, Args&&... args)
{
    this->log(Level::Error, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
inline void nail::Logger::critical(std::string_view const fmt, Args&&... args)
{
    this->log(Level::Critical, fmt, std::forward<Args>(args)...);
}

inline std::string const& nail::Logger::getID() const noexcept
{
    return m_id;
}

inline nail::Logger::Level nail::Logger::getLogLevel() const noexcept
{
    return m_logLevel;
}

