template<typename Event>
template<typename Fn>
inline nail::EventSubscriber<Event>::EventSubscriber(Fn callback)
    : m_callback(callback) {}

template<typename Event>
inline void nail::EventSubscriber<Event>::update(Event& event)
{
    if (m_callback)
        m_callback(event);
}

template<typename Event>
template<typename Fn>
inline void nail::EventSubscriber<Event>::setCallback(Fn callback)
{
    m_callback = callback;
}

