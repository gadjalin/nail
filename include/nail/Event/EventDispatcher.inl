template<typename Event>
template<typename Fn>
inline nail::EventDispatcher<Event>::EventDispatcher(Fn callback)
    : m_callback(callback) {}

template<typename Event>
inline void nail::EventDispatcher<Event>::update(Event& event)
{
    dispatch(event);
}

template<typename Event>
inline void nail::EventDispatcher<Event>::dispatch(Event& event)
{
    if (m_callback)
        m_callback(event);
}

template<typename Event>
template<typename Fn>
inline void nail::EventDispatcher<Event>::setCallback(Fn callback)
{
    m_callback = callback;
}

