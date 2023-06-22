template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>::Ranged() noexcept
    : m_value(Default) {}

template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>::Ranged(Type const& value)
{
    *this = value;
}

template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>::Ranged(Type&& value)
{
    *this = std::move(value);
}

template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>& nail::Ranged<Type, Min, Max, Default>::operator=(Type const& value)
{
    if (isInRange(value))
    {
        m_value = value;
        return *this;
    }
    else
    {
        defaultsAndThrow(value);
    }
}

template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>& nail::Ranged<Type, Min, Max, Default>::operator=(Type&& value)
{
    if (isInRange(value))
    {
        m_value = std::exchange(value, {});
        return *this;
    }
    else
    {
        defaultsAndThrow(value);
    }
}

template<typename Type, Type Min, Type Max, Type Default>
inline nail::Ranged<Type, Min, Max, Default>::operator Type() const noexcept
{
    return m_value;
}

template<typename Type, Type Min, Type Max, Type Default>
inline constexpr bool nail::Ranged<Type, Min, Max, Default>::isInRange(Type const& value) const noexcept
{
    return value >= Min && value <= Max;
}

template<typename Type, Type Min, Type Max, Type Default>
inline void nail::Ranged<Type, Min, Max, Default>::defaultsAndThrow(Type const& badValue)
{
    m_value = Default;
    throw std::invalid_argument(fmt::format("Value must be in range ({:+d},{:+d}): {:+d} was given.", Min, Max, badValue));
}

