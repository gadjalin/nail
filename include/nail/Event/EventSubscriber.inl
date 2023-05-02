template<typename Event>
template<typename Fn>
inline nail::EventSubscriber<Event>::EventSubscriber(Fn callback)
    : m_callback(callback) {}

template<typename Event>
inline void nail::EventSubscriber<Event>::operator()(Event& event) const
{
    m_callback(event);
}

template<typename Event>
template<typename Fn>
inline void nail::EventSubscriber<Event>::setCallback(Fn callback) noexcept
{
    m_callback = callback;
}

