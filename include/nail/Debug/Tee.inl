template<typename Print>
constexpr nail::Tee<Print>::Tee(Print print)
    : m_print(print) {}

template<typename Print>
template<typename V>
inline auto nail::Tee<Print>::operator()(V&& value) const -> decltype(std::forward<V>(value))
{
    std::invoke(m_print, value);
    return std::forward<V>(value);
}

constexpr nail::Tee<std::ostream>::Tee(std::ostream& os)
    : m_os(os) {}

template<typename V>
inline auto nail::Tee<std::ostream>::operator()(V&& value) const -> decltype(std::forward<V>(value))
{
    m_os << value << std::endl;
    return std::forward<V>(value);
}

constexpr nail::Tee<char const*>::Tee(char const* const file)
    : m_path(file) {}

template<typename V>
inline auto nail::Tee<char const*>::operator()(V&& value) const -> decltype(std::forward<V>(value))
{
    std::ofstream file(m_path, std::ios_base::out | std::ios_base::trunc);

    if (file)
        file << value << std::endl;
    else
        std::perror("Unable to tee");

    return std::forward<V>(value);
}

template<typename Print>
constexpr nail::Tee<Print> nail::make_tee(Print print)
{
    return Tee<Print>(print);
}

constexpr nail::Tee<std::ostream> nail::make_tee(std::ostream& os)
{
    return Tee<std::ostream>(os);
}

constexpr nail::Tee<char const*> nail::make_tee(char const* const file)
{
    return Tee<char const*>(file);
}

template<typename V, typename TeeType>
inline auto operator|(V&& value, nail::Tee<TeeType> const& tee_) -> decltype(std::forward<V>(value))
{
    return std::forward<V>(tee_(value));
}

