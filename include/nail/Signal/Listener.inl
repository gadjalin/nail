template<typename Return, typename... Args>
template<typename Fn>
nail::Listener<Return (Args...)>::Listener(Fn callback)
    : m_callback(callback) {}

template<typename Return, typename... Args>
template<typename Fn>
inline void nail::Listener<Return (Args...)>::setCallback(Fn callback)
{
    m_callback = callback;
}

template<typename Return, typename... Args>
inline Return nail::Listener<Return (Args...)>::update(Args&&... args)
{
    // TODO: Handle empty callback ? (std::function already throws an exception)
    return m_callback(std::forward<Args>(args)...);
}

