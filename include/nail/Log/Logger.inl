template<typename T>
inline void nail::Logger::log(Level const level, T const& line)
{
    this->log(level, "{}", line);
}

template<typename... Args>
inline void nail::Logger::log(Level const level, std::string_view const fmt, Args&&... args)
{
    this->write(level, fmt::format(fmt, std::forward<Args>(args)...));
}

template<typename T>
inline void nail::Logger::debug(T const& line)
{
    this->log(Level::Debug, line);
}

template<typename T>
inline void nail::Logger::info(T const& line)
{
    this->log(Level::Info, line);
}

template<typename T>
inline void nail::Logger::warn(T const& line)
{
    this->log(Level::Warn, line);
}

template<typename T>
inline void nail::Logger::error(T const& line)
{
    this->log(Level::Error, line);
}

template<typename T>
inline void nail::Logger::critical(T const& line)
{
    this->log(Level::Critical, line);
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

