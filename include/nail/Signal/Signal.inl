template<typename... Args>
inline void nail::Signal<Args...>::listen(Listener& listener)
{
    m_listeners.insert(&listener);
}

template<typename... Args>
inline void nail::Signal<Args...>::quit(Listener& listener)
{
    m_listeners.erase(&listener);
}

template<typename... Args>
inline void nail::Signal<Args...>::emit(Args&&... args)
{
    for (auto& listener : m_listeners)
        listener->update(std::forward<Args>(args)...);
}

