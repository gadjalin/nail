template<typename Return, typename... Args>
template<typename Fn>
nail::Listener<Return (Args...)>::Listener(Fn const callback)
   : m_callback(callback) {}

template<typename Return, typename... Args>
template<typename Fn>
inline void nail::Listener<Return (Args...)>::setCallback(Fn const callback)
{
    m_callback = callback;
}

template<typename Return, typename... Args>
inline Return nail::Listener<Return (Args...)>::update(Args&&... args)
{
    return m_callback(std::forward<Args>(args)...);
}

