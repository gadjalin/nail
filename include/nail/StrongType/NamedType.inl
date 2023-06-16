template<typename Underlying, typename Tag>
inline nail::NamedType<Underlying, Tag>::NamedType(Underlying const& value)
    : m_value(value) {}

template<typename Underlying, typename Tag>
template<typename T, typename>
inline nail::NamedType<Underlying, Tag>::NamedType(Underlying&& value)
    : m_value(std::move(value)) {}

template<typename Underlying, typename Tag>
inline Underlying& nail::NamedType<Underlying, Tag>::get() noexcept
{
    return m_value;
}

template<typename Underlying, typename Tag>
inline Underlying const& nail::NamedType<Underlying, Tag>::get() const noexcept
{
    return m_value;
}

template<typename Underlying, typename Tag>
inline Underlying* nail::NamedType<Underlying, Tag>::operator->() noexcept
{
    return std::addressof(m_value);
}

template<typename Underlying, typename Tag>
inline Underlying const* nail::NamedType<Underlying, Tag>::operator->() const noexcept
{
    return std::addressof(m_value);
}

template<typename Underlying, typename Tag>
inline Underlying& nail::NamedType<Underlying, Tag>::operator*() & noexcept
{
    return m_value;
}

template<typename Underlying, typename Tag>
inline Underlying const& nail::NamedType<Underlying, Tag>::operator*() const& noexcept
{
    return m_value;
}

template<typename Underlying, typename Tag>
inline Underlying&& nail::NamedType<Underlying, Tag>::operator*() && noexcept
{
    return std::move(m_value);
}

template<typename Underlying, typename Tag>
inline Underlying const&& nail::NamedType<Underlying, Tag>::operator*() const&& noexcept
{
    return std::move(m_value);
}

