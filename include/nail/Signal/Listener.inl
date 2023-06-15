template<typename... Args>
template<typename Fn>
nail::Listener<Args...>::Listener(Fn callback)
    : m_callback(callback) {}

template<typename... Args>
template<typename Fn>
inline void nail::Listener<Args...>::setCallback(Fn callback)
{
    m_callback = callback;
}

template<typename... Args>
inline void nail::Listener<Args...>::update(Args&&... args)
{
    if (m_callback)
        m_callback(std::forward<Args>(args)...);
}

