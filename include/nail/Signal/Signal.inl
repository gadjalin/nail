template<typename Return, typename... Args>
inline void nail::Signal<Return (Args...)>::listen(Listener& listener)
{
    m_listeners.insert(&listener);
}

template<typename Return, typename... Args>
inline void nail::Signal<Return (Args...)>::quit(Listener& listener)
{
    m_listeners.erase(&listener);
}

template<typename Return, typename... Args>
inline void nail::Signal<Return (Args...)>::emit(Args&&... args)
{
    auto listeners = m_listeners;
    for (auto& listener : listeners)
        listener->update(std::forward<Args>(args)...);
}

