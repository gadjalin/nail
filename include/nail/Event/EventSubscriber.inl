template<typename Event, typename Type>
template<typename Fn>
inline nail::EventSubscriber<Event, Type>::EventSubscriber(Type type, Fn callback)
    : m_eventType(type), m_callback(callback) {}

template<typename Event, typename Type>
inline void nail::EventSubscriber<Event, Type>::update(Event& event)
{
    if (m_callback && event.getType() == m_eventType)
        m_callback(event);
}

template<typename Event, typename Type>
template<typename Fn>
inline void nail::EventSubscriber<Event, Type>::setCallback(Fn callback)
{
    m_callback = callback;
}

template<typename Event, typename Type>
inline void nail::EventSubscriber<Event, Type>::setType(Type type)
{
    m_eventType = type;
}

