inline bool nail::DynamicLibrary::isLoaded() const noexcept
{
    return static_cast<bool>(m_handle);
}

inline nail::DynamicLibrary::operator bool() const noexcept
{
    return isLoaded();
}

inline void* nail::DynamicLibrary::getHandle() const noexcept
{
    return m_handle;
}

inline std::string const& nail::DynamicLibrary::getName() const noexcept
{
    return m_name;
}

